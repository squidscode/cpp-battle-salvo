#include "factories/GameFactory.hpp"
#include "factories/human_vs_ai/HumanVsAIFactory.hpp"
#include "factories/ai_vs_ai/AIVSAIFactory.hpp"
#include "factories/aggregator/AggregatorFactory.hpp"
#include "model/player/strategies/setup/SetupStrategy.hpp"
#include "model/player/strategies/setup/random/RandomSetup.hpp"
#include "model/player/strategies/shot/ShotStrategy.hpp"
#include "model/player/strategies/shot/random/RandomShot.hpp"
#include "model/player/strategies/shot/heat_map/HeatMap.hpp"
#include <vector>
#include <iostream>

#define btos(b)     (b ? "true" : "false")

void printerr_setup_options();
void print_help_message(std::ostream*);
Model::SetupStrategy *parse_setup(char *c);
Model::ShotStrategy *parse_shot(char *c);

int main(int argc, char* argv[]) {
    Factory::GameFactory *gf;
    if(argc == 1) {
        gf = new Factory::HumanVsAIFactory();
    } else if(argc == 2) {
        if(strcmp(argv[1], "ai_vs_ai") == 0) {
            gf = new Factory::AIVSAIFactory();
        } else { // error
            std::cerr <<  "Invalid setup option, the valid options are:\n";
            printerr_setup_options();
            exit(1);
        }
    } else {
        int ind = 1;
        Model::SetupStrategy *setup = new Model::RandomSetup;
        Model::ShotStrategy *shot = new Model::RandomShot;
        LOOP: 
        if(strcmp(argv[1], "--aggregate") == 0 && argc == 7) {
            int numGames = atoi(argv[2]);
            Model::SetupStrategy *setup1 = parse_setup(argv[3]);
            Model::SetupStrategy *setup2 = parse_setup(argv[4]);
            Model::ShotStrategy *shot1 = parse_shot(argv[5]);
            Model::ShotStrategy *shot2 = parse_shot(argv[6]);
            gf = new Factory::AggregatorFactory(numGames, setup1, setup2, shot1, shot2);
        } else if(strcmp(argv[ind], "--setup") == 0) {
            ind++;
            delete setup;
            setup = parse_setup(argv[ind++]);
            if(ind < argc) goto LOOP;
            gf = new Factory::HumanVsAIFactory(setup, shot);
        } else if(strcmp(argv[ind], "--shot") == 0) {
            ind++;
            delete shot;
            shot = parse_shot(argv[ind++]);
            if(ind < argc) goto LOOP;
            gf = new Factory::HumanVsAIFactory(setup, shot);
        } else if(strcmp(argv[ind], "ai_vs_ai") == 0 && argc == 6) {
            Model::SetupStrategy *setup1 = parse_setup(argv[2]);
            Model::SetupStrategy *setup2 = parse_setup(argv[3]);
            Model::ShotStrategy *shot1 = parse_shot(argv[4]);
            Model::ShotStrategy *shot2 = parse_shot(argv[5]);
            gf = new Factory::AIVSAIFactory(setup1, setup2, shot1, shot2);
        } else {
            std::cerr << "Invalid argument!\n";
            print_help_message(&std::cerr);
            exit(1);
        }
    }
    gf->CreateController()->Run();
    delete gf;
}

void printerr_setup_options() {
    std::vector<std::string> options{"ai_vs_ai"};
    for(int i = 0; i < options.size(); ++i) {
        std::cerr << "- " << options[i] << "\n";
    }
}

void print_help_message(std::ostream *out) {
    *out << "TODO: HELP MESSAGE\n";
}

Model::SetupStrategy *parse_setup(char *c) {
    if(strcmp(c, "random-setup") == 0) {
        return new Model::RandomSetup;
    } else {
        std::cerr <<  "Invalid setup strategy!\n";
        print_help_message(&std::cerr);
        exit(1);
    }
}

Model::ShotStrategy *parse_shot(char *c) {
    std::string str;
    if(strcmp(c, "random-shot") == 0) {
        return new Model::RandomShot;
    } else if((str = std::string(c).substr(0, 12), strcmp(str.c_str(), "heatmap-shot") == 0)) {
        bool enable{false}; bool rand{true};
        int min_ratio = 4; int compound = 0; int ind = -1;
        char *token = strtok(c, "-");
        while((ind++, token != NULL)){
            if(ind == 1) enable = (strlen(token) > 4 && token[4] == 'D');
            if(ind == 1) rand = !(strlen(token) > 5 && token[5] == 'R');
            if(ind == 2) min_ratio = atoi(token);
            if(ind == 3) compound = atoi(token);
            token = strtok(NULL, "-");
        }
        printf("CONFIG: (enable_delegate->min_ratio, rand_tiebreaking, compound) = (%s->%d, %s, %d)\n", btos(enable), min_ratio, btos(rand), compound);
        return new Model::HeatMapStrategy(new Model::RandomShot, enable, min_ratio, rand, compound);
    } else {
        std::cerr <<  "Invalid setup strategy!\n";
        print_help_message(&std::cerr);
        exit(1);
    }
}
