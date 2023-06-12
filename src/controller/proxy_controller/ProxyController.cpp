#include "ProxyController.hpp"
#include <stdexcept>
#include <unistd.h>

using namespace Controller;

ProxyController::ProxyController(const char* username, GameType gt, int socket_fd, Model::Player *player) {
    this->username = username;
    this->gameType = gt;
    this->socket_fd = socket_fd;
    this->player = player;
}

void ProxyController::Run() {
    char buf[1024] = {0};
    size_t sz;
    while( 0 != (sz = read(this->socket_fd, &buf, sizeof(buf))) ) {
        buf[sz] = '\0';
        // printf("RECEIVED: %s", buf);
        this->HandleReceivedMsg(json::parse(buf));
    }
}

void ProxyController::HandleReceivedMsg(const json& msg) {
    assert(!msg["method-name"].is_null());
    std::string msg_str = msg["method-name"].dump();
    int last_ind = msg_str.size() - 1;
    assert((msg_str[0] == '\'' && msg_str[last_ind] == '\'') 
        || (msg_str[0] == '"' && msg_str[last_ind] == '"'));
    msg_str = msg_str.substr(1, msg_str.size() - 2);
    std::map<std::string, void (ProxyController::*)(const json&)> method_name_map{
        {"join", &ProxyController::HandleJoin},
        {"setup", &ProxyController::HandleSetup},
        {"take-shots", &ProxyController::HandleTakeShots},
        {"report-damage", &ProxyController::HandleReportDamage},
        {"successful-hits", &ProxyController::HandleSuccessfulHits},
        {"end-game", &ProxyController::HandleEndGame}
    };
    if(method_name_map.count(msg_str) > 0) {
        (this->*method_name_map[msg_str])(msg["arguments"]);
    } else {
        throw std::runtime_error("Invalid method-name argument in received message: " + msg.dump());
    }
}

json ProxyController::JsonTemplate(const char* method_name) {
    json msg;
    msg["method-name"] = method_name;
    return msg;
}

void ProxyController::HandleJoin(const json& arguments) {
    assert(arguments.dump() == "{}");   // this should always be true
    // ignore the arguments provided for join.
    json response = this->JsonTemplate("join");
    response["arguments"]["name"] = this->username;
    response["arguments"]["game-type"] = (this->gameType == SINGLE ? "SINGLE" : "MULTI");
    this->SendMsg(response);
}

void ProxyController::HandleSetup(const json& arguments) {
    json response = this->JsonTemplate("setup");
    // printf("width: %s, height: %s\n", arguments["width"].dump().c_str(), arguments["height"].dump().c_str());
    // printf("SUB: %s, DESTROYER: %s, BATTLESHIP: %s, CARRIER: %s\n", );
    int width = atoi(arguments["width"].dump().c_str()); int height = atoi(arguments["height"].dump().c_str());
    Map<Model::ShipType, int> ship_freq;
    ship_freq.Insert(Model::ShipType::SUBMARINE,  atoi(arguments["fleet-spec"]["SUBMARINE"].dump().c_str()));
    ship_freq.Insert(Model::ShipType::DESTROYER,  atoi(arguments["fleet-spec"]["DESTROYER"].dump().c_str()));
    ship_freq.Insert(Model::ShipType::BATTLESHIP, atoi(arguments["fleet-spec"]["BATTLESHIP"].dump().c_str()));
    ship_freq.Insert(Model::ShipType::CARRIER,    atoi(arguments["fleet-spec"]["CARRIER"].dump().c_str()));
    Iterator<Model::Ship> ships = this->player->Setup(width, height, &ship_freq);
    std::vector<json> fleet;
    while(ships.HasNext()) {
        Model::Ship nxt_ship = ships.Next();
        json ship_json;
        ship_json["coord"]["x"] = nxt_ship.GetTopLeftCoord().first;
        ship_json["coord"]["y"] = nxt_ship.GetTopLeftCoord().second;
        ship_json["length"] = ((int) nxt_ship.GetShipType());       // typecast for clarity -- Note: ShipType is an int.
        ship_json["direction"] = (nxt_ship.GetDirection() == Model::Direction::HORIZONTAL ? "HORIZONTAL" : "VERTICAL");
        fleet.push_back(ship_json);
    }
    response["arguments"]["fleet"] = fleet;
    this->SendMsg(response);
}

void ProxyController::HandleTakeShots(const json& arguments) {
    json response = this->JsonTemplate("take-shots");
    Iterator<std::pair<int,int>> shots = this->player->TakeShots();
    std::vector<json> json_shots;
    while(shots.HasNext()) {
        std::pair<int,int> nxt_shot = shots.Next();
        json json_shot;
        json_shot["x"] = nxt_shot.first;
        json_shot["y"] = nxt_shot.second;
        json_shots.push_back(json_shot);
    }
    response["arguments"]["coordinates"] = json_shots;
    this->SendMsg(response);
}

void ProxyController::HandleReportDamage(const json& arguments) {
    json response = this->JsonTemplate("report-damage");
    std::vector<std::pair<int,int>> opponent_shots_v;
    for(json opponent_shots : arguments["coordinates"]) {
        opponent_shots_v.push_back({atoi(opponent_shots["x"].dump().c_str()), atoi(opponent_shots["y"].dump().c_str())});
    }
    Iterator<std::pair<int,int>> opshots_it(opponent_shots_v);
    Iterator<std::pair<int,int>> successful_hits = this->player->ReportDamage(&opshots_it);
    std::vector<json> json_hits;
    while(successful_hits.HasNext()) {
        std::pair<int,int> nxt_shot = successful_hits.Next();
        json json_shot;
        json_shot["x"] = nxt_shot.first;
        json_shot["y"] = nxt_shot.second;
        json_hits.push_back(json_shot);
    }
    response["arguments"]["coordinates"] = json_hits;
    this->SendMsg(response);
}

void ProxyController::HandleSuccessfulHits(const json& arguments) {
    json response = this->JsonTemplate("successful-hits");
    std::vector<std::pair<int,int>> successful_hits_v;
    for(json hits : arguments["coordinates"]) {
        successful_hits_v.push_back({atoi(hits["x"].dump().c_str()), atoi(hits["y"].dump().c_str())});
    }
    Iterator<std::pair<int,int>> successful_hits_it(successful_hits_v);
    this->player->SuccessfulHits(&successful_hits_it);
    response["arguments"] = "{}"_json;
    this->SendMsg(response);
}

void ProxyController::HandleEndGame(const json& arguments) {
    json response = this->JsonTemplate("end-game");
    response["arguments"] = "{}"_json;
    this->SendMsg(response);
}

void ProxyController::SendMsg(const json& msg) {
    std::string msg_str = msg.dump();
    // printf("SENDING: %s\n", msg_str.c_str());
    // printf("SENDING: %s\n", msg.dump(2).c_str());
    write(this->socket_fd, (msg_str + "\n").c_str(), msg_str.size());
}


/*
-----------------------------------------
TODO: create methods for each 
  - parse string
  - handle join
  - handle setup
  - handle take-shots
  - handle report-damage
  - handle successful-hits
  - handle end-game


-----------------------------------------
REQUEST:
{
	"method-name": "join",
	"arguments": {}
}
RESPONSE:
{
	"method-name": "join",
	"arguments": {
		"name": "github_username",
		"game-type": "SINGLE" / "MULTI"
	}
}

{
	"method-name": "setup",
	"arguments": {
		"width": 10,
		"height": 10,
		"fleet-spec": {
			"CARRIER": 2,
			"BATTLESHIP": 4,
		  "DESTROYER": 1,
			"SUBMARINE": 3
		}
	}
}
{
	"method-name": "setup",
	"arguments": {
		"fleet": [
		  {
				"coord": {"x": 0, "y": 0}, 
				"length": 6,
				"direction": "VERTICAL"
			}, 
		  {
				"coord": {"x": 1, "y": 0}, 
				"length": 5,
				"direction": "HORIZONTAL"
			}
		]
	}
}

{
	"method-name": "take-shots",
	"arguments": {}
}
{
	"method-name": "take-shots",
	"arguments": {
		"coordinates": [
			{"x": 4, "y": 2},
			{"x": 7, "y": 1}
		]
	}
}

{
	"method-name": "report-damage",
	"arguments": {
		"coordinates": [
			{"x": 0, "y": 1},
			{"x": 3, "y": 2}
		]
	}
}
{
	"method-name": "report-damage",
	"arguments": {
		"coordinates": [
			{"x": 3, "y": 2}
		]
	}
}

{
	"method-name": "successful-hits",
	"arguments": {
		"coordinates": [
			{"x": 0, "y": 1},
			{"x": 3, "y": 2}
		]
	}
}
{
	"method-name": "successful-hits",
	"arguments": {}
}

{
	"method-name": "end-game",
	"arguments": {
		"result": "WIN" / "LOSE" / "DRAW",
		"reason": "Player 1 sank all of Player 2's ships"
	}
}
{
	"method-name": "end-game",
	"arguments": {}
}
*/