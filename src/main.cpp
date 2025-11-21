#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "Pattern.h"
#include "HopfieldNetwork.h"
#include "UI.h"
#include "FileUtils.h"
#include "DefaultPatterns.h"

const std::string FILENAME = "patterns.txt";

int main() {
    std::vector<Matrix> patterns;
    HopfieldNetwork network;

    std::cout << "=== HOPFIELD NETWORKS - COMPLETE SYSTEM ===\n";
    std::cout << "Pattern recognition and reconstruction system 5x5\n\n";

    loadPatterns(patterns, FILENAME);


    network.train(patterns);
    std::cout << "Network trained on " << patterns.size() << " patterns.\n";

    while (true) {
        UI::printMenu();

        if (!UI::handleMenuChoice(patterns, network, FILENAME)) {
            break; // Zakończ pętlę
        }
    }
    return 0;
}
