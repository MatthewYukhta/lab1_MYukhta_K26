// compiler used: MSVC

#include "carddeck.h"
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

// Creates stacks of cards for statistic processing.
// ARGUMENTS:
// card_num - the amount of cards to draw.
// deck - the deck that supplies the cards.
// RETURN VALUE:
// deque with lengths of created stacks sorted in ascending order.
deque<int> stack_creator(int card_num, Carddeck& deck)
{
    if (card_num <= 0) throw invalid_argument("Must draw a positive amount of cards");

    deque<int> stack_lens;
    int cards_drawn = 0;
    deque<Card> cardstack;

    while (cards_drawn != card_num)
    {
        Card cur_card = deck();
        if (!cardstack.empty() && cur_card <= cardstack.back())
        {
            stack_lens.push_back(cardstack.size());
            cardstack.clear();
        }
        cardstack.push_back(cur_card);
        ++cards_drawn;
    }
    
    sort(stack_lens.begin(), stack_lens.end());
    return stack_lens;
}

// Computes frequency and mode of stacks' length.
void stack_freqs(deque<int> lens)
{
    if (lens.empty()) throw invalid_argument("Empty lengths list given!");
    map<int, int> len_freqs;
    double proc = 100.0;
    int freq = 1;
    auto it = lens.begin(), it_n = it;
    ++it_n;
    while (it != lens.end())
    {
        if (it_n != lens.end() && *it_n == *it) ++freq;
        else
        {
            len_freqs.insert({*it, freq});
            freq = 1;
        }
        ++it;
        if (it_n != lens.end()) ++it_n;
    }

    int key = 1;
    while (key <= *(--lens.end()))
    {
        if (len_freqs.contains(key)) cout << format("Length {}: {:.3f}%", key, len_freqs[key] * proc / lens.size()) << endl;
        else cout << format("Length {}: 0%", key) << endl;
        ++key;
    }

    int max_freq = 0;
    deque<int> mode_lens;
    cout << "Most common stack length frequencies:" << endl;
    for (auto it = len_freqs.begin(); it != len_freqs.end(); ++it)
    {
        if (it->second > max_freq)
        {
            max_freq = it->second;
            mode_lens.clear();
            mode_lens.push_back(it->first);
        }
        else if (it->second == max_freq)
        {
            mode_lens.push_back(it->first);
        }
    }

    for (auto it = mode_lens.begin(); it != mode_lens.end(); ++it)
    {
        cout << *it << ' ';
    }
    cout << endl;
}

double stack_mean(deque<int> lens)
{
    if (lens.empty()) throw invalid_argument("Empty lengths list given!");

    double sum = 0;
    for (auto it = lens.begin(); it != lens.end(); ++it)
    {
        sum += *it;
    }
    return sum / lens.size();
}

double stack_median(deque<int> lens)
{
    if (lens.empty()) throw invalid_argument("Empty lengths list given!");
    
    if (lens.size() % 2 != 0) return *(lens.begin() + (lens.size() - 1) / 2);
    else return 0.5 * (*(lens.begin() + (lens.size() / 2) - 1) + *(lens.end() - (lens.size() / 2)));
}

int main()
{
    cout << "Welcome to card deck simulator!" << endl;
    cout << "Specify the suit capacity: ";
    try
    {
        int s_cap;
        cin >> s_cap;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw ios_base::failure("Expected a number");
        }

        Carddeck deck1(s_cap);
        int card_num;
        cout << "How many cards to draw: ";
        cin >> card_num;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw ios_base::failure("Not a number received");
        }

        deque<int> stacks = stack_creator(card_num, deck1);
        stack_freqs(stacks);
        cout << "Mean stack length: " << stack_mean(stacks) << endl;
        cout << "Median stack length: " << stack_median(stacks) << endl;
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
    }
}