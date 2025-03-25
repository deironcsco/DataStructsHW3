

#include "Deck.h"
#include "SidePile.h"
#include <cstdlib> //for random
#include <ctime>   //for random
#include <iostream>
#include <limits>

void InitializeDeck(Deck &);

int main() {

  // initialzie random
  std::srand(1);

  // vars
  Deck player_deck;
  Deck com_deck;
  SidePile player_sidepile;
  SidePile com_sidepile;

  // initialize decks (shuffles them)
  InitializeDeck(player_deck);
  InitializeDeck(com_deck);

  // more vars
  bool forfeit{false};
  bool game_over{false};
  int player_card{0};
  int com_card{0};
  int player_side_card{0};
  int com_side_card{0};
  bool skip{ false };

  // start game
  std::cout << "Game Start!\n";

  while (!forfeit && !game_over) {

    // choose to peek or to play (prompt slightly different on if user has
    // choice after peeking)
    int user_input{0};
    if (player_sidepile.IsEmpty()) {
      std::cout
          << "Press 1 to play a card from the top of your deck.\n"
          << "Press 2 to peek at the top card and add it to the side pile.\n"
          << "Press 3 to see how many cards you have in your deck and side "
             "pile.\n"
          << "Press 4 to forfeit.\n>";
    } else {
      std::cout << "Press 1 to play a card from the top of your deck.\n"
                << "Press 2 to peek at the top card then chooose to add to "
                   "side pile or to play in addition with top of side pile.\n"
                << "Press 3 to see how many cards you have in your deck and "
                   "side pile.\n"
                << "Press 4 to forfeit.\n>";
    }
    // input validation
    while (!(std::cin >> user_input)) {
      std::cin.clear(); // clear flags? idk
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n'); // clear buffer
    }

    // switch case based on user choice
    switch (user_input) {
    case (1): {
      // play the card

      player_card = player_deck.Dequeue();
      std::cout << "Player card: " << player_card << " ";
      break;
    }
    case (2): {
      // peek card

      // display peeked card
      int peek_card = player_deck.Peek();
      std::cout << "Your card is: " << peek_card << '\n';

      // check if side pile is empty before giving choice, force it to the top
      // of the side pile if its empty
      if (player_sidepile.IsEmpty()) {

        // info message because side pile is empty
        std::cout << "Because your side pile is empty, you can't add this card "
                     "with the top card of the side pile.\n"
                  << "This card will be added to the top of the side pile.\n"
                  << "Input any number to continue.\n>";

        // take input, with input validation, just to pause
        while (!(std::cin >> user_input)) {
          std::cin.clear(); // clear flags? idk
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                          '\n'); // clear buffer
        }

        peek_card = player_deck.Dequeue(); // take card from deck
        player_sidepile.Push(peek_card);   // add to side pile
        std::cout << "Your card was added to the side pile!\n";
        player_card = player_deck.Dequeue(); // play next card in deck
        std::cout << "You drew the next card!\n";
        std::cout << "Player card: " << player_card << " ";
      } else {

        // side pile not empty, player has choice)
        bool proper_input{false}; // repeat until user makes a good input
        while (!proper_input) {
          proper_input = true;
          std::cout
              << "Press 1 to play with this card added to the top card of your "
                 "side pile.\n"
              << "Press 2 to add this card to the top of your side pile.\n>";
          // input validation
          while (!(std::cin >> user_input)) {
            std::cin.clear(); // clear flags? idk
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n'); // clear buffer
          }

          // user input
          switch (user_input) {
          case (1): {

            // play with top card of side pile
            int top_of_deck = player_deck.Dequeue();
            int top_of_sidepile = player_sidepile.Pop();
            player_card = top_of_deck + top_of_sidepile;
            player_side_card = top_of_sidepile;
            std::cout << "Player card: " << top_of_deck << " (deck) + "
                      << top_of_sidepile << " (side pile) ";
            break;
          }
          case (2): {

            // add to top of side pile
            player_card = player_deck.Dequeue();
            player_sidepile.Push(player_card);
            std::cout << "Your card was added to the side pile!\n";
            player_card = player_deck.Dequeue(); // take next card to use
            std::cout << "You drew the next card!\n";
            std::cout << "Player card: " << player_card << " ";
            break;
          }
          default: {

            proper_input = false;
            std::cout << "Invalid input.\n";
            break;
          }
          }
        }
      }
      break;
    }
    case (3): {

      // see cards in decks/side pile
      std::cout << "Cards in deck: " << player_deck.DeckSize() << '\n';
      std::cout << "Cards in side pile: " << player_sidepile.PileSize() << '\n';
      skip = true;
      break;
    }
    case (4): {

      // forfeit
      forfeit = true;
      break;
    }
    default: {

      std::cout << "Invalid input.\n";
      break;
    }
    }

    // computer peek or play, random choice, assuming no forfeit
    if (!forfeit && !skip) {
      int com_choice = std::rand() % 2;
      switch (com_choice) {
      case (0): {
        // play

        com_card = com_deck.Dequeue();
        std::cout << "COM card: " << com_card << '\n';
        break;
      }
      case (1): {
        // peek

        // if peek choose to side pile if it contains one, or to play
        if (com_sidepile.IsEmpty()) {
          // add to side pile

          com_sidepile.Push(com_deck.Dequeue());
          std::cout << "COM added a card to its side pile!\n";
          com_card = com_deck.Dequeue();
          std::cout << "COM card: " << com_card << '\n';
        } else {
          // choose to either add to side pile or play

          com_choice = std::rand() % 2;
          switch (com_choice) {
          case (0): {
            // add to side pile

            com_sidepile.Push(com_deck.Dequeue());
            std::cout << "COM added a card to its side pile!\n";
            com_card = com_deck.Dequeue();
            std::cout << "COM card: " << com_card << '\n';
            break;
          }
          case (1): {
            // play with top of side pile

            int top_of_deck = com_deck.Dequeue();
            int top_of_sidepile = com_sidepile.Pop();
            std::cout << "COM card: " << top_of_deck << " (deck) + "
                      << top_of_sidepile << " (side pile)\n";
            com_card = top_of_deck = top_of_sidepile;
            com_side_card = top_of_sidepile;
            break;
          }
          default: {

            std::cout << "COMPUTER ERROR\n";
            break;
          }
          }
        }

        break;
      }
      default: {
        std::cout << "COMPUTER ERROR\n";
        break;
      }
      }
      // determine results, add cards to winner's deck
      if (player_card > com_card) {
        // player win
        std::cout << "You won that round!\n";

        // add cards to bottom of player deck

        if (com_side_card != 0) {
          player_deck.Enqueue(com_card - com_side_card);
          player_deck.Enqueue(com_side_card);
        } else {
          player_deck.Enqueue(com_card);
        }
        if (player_side_card != 0) {
          player_deck.Enqueue(player_card - player_side_card);
          player_deck.Enqueue(player_side_card);
        } else {
          player_deck.Enqueue(player_card);
        }
      } else {
        // com win
        std::cout << "COM won that round!\n";

        // add cards to bottom of com deck
        if (player_side_card != 0) {
          com_deck.Enqueue(player_card - player_side_card);
          com_deck.Enqueue(player_side_card);
        } else {
          com_deck.Enqueue(player_card);
        }
        if (com_side_card != 0) {
          com_deck.Enqueue(com_card - com_side_card);
          com_deck.Enqueue(com_side_card);
        } else {
          com_deck.Enqueue(com_card);
        }
      }
      // reset side cards
      player_side_card = 0;
      com_side_card = 0;

      // check if game over
      if (player_deck.DeckSize() == 0 || com_deck.DeckSize() == 0) {
        game_over = true;
      }

    } // forfeit check end bracket
    skip = false;
    std::cout << "\n";
  } //while loop end

  // determine who wins or loses / forfeit
  if (forfeit) {
    // forfeit
    std::cout << "You lost to forfeit!\n";
    return 0;
  }
  if (com_deck.DeckSize() == 0) {
    // com loses
    std::cout << "You win!\n";
    return 0;
  }
  if (player_deck.DeckSize() == 0) {
    std::cout << "You Lose!\n";
    return 0;
  }
  std::cout << "Error";
  return 0;
}

/*
 * we will have an array of the numbers we want to put in the deck
 * use random to pick one
 * and decrease size of array (perhaps declaring a new one?)
 */
void InitializeDeck(Deck &d) {

  // vars
  int OGsize{52}; // original size of a deck
  int cards[52] = {2,  2,  2,  2,  3,  3,  3,  3,  4,  4,  4,  4,  5,
                   5,  5,  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,
                   8,  8,  9,  9,  9,  9,  10, 10, 10, 10, 11, 11, 11,
                   11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14};
  // 11 = jack, 12 = queen, 13 = king, 14 = ace
  int temp[52];
  int size = OGsize; // size used in the while loop, will gradually decrease as
                     // i pick elements to add to deck

  // for length of array
  for (int i{0}; i < OGsize; i++) {
    // randomly pick one and add to deck
    int rand_index = std::rand() % size;
    d.Enqueue(cards[rand_index]);

    // declare a new array thats a size smaller and add everything except that
    // value into it
    for (int i{0}; i < rand_index; i++) {
      temp[i] = cards[i];
    }
    for (int i{rand_index}; i < size - 1; i++) {
      temp[i] = cards[i + 1];
    }

    // copy temp to cardss
    for (int i{0}; i < size - 1; i++) {
      cards[i] = temp[i];
    }

    // decrement size
    size = size - 1;
  }
}
