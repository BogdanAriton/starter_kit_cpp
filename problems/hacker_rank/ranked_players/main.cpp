#include <iostream>
#include <vector>
#include <string>
//#include <algorithm>
using namespace std;
// 100 100 50 40 40 20 10
// 5 25 50 120

int getPosition(const vector<int>&, int, int, const int&);
vector<int> stripDups(const vector<int>&);

void printVec(const vector<int> & v)
{
    cout << "<<<<<< Start >>>>>>" << endl;
    for (const auto& item: v)
    {
        cout << item << endl;
    }
    cout << "<<<<<< End >>>>>>" << endl;
}

vector<int> climbingLeaderboard(const vector<int>& ranked, const vector<int>& player) {
    vector<int> strip = stripDups(ranked);
    printVec(strip);

    vector<int> result{};
    
    for (auto it = player.begin(); it != player.end(); ++it)
    {
        cout << *it << " comp " << *strip.begin() << endl;
        cout << *it << " comp " << *(strip.end()-1) << endl;
        if (*it >= *strip.begin()) // it's first
        {
            //cout << "Is first: " << "item = " << *it << " compared to " << *strip.begin() << endl;
            result.push_back(1);
        }
        else if (*it < *(strip.end()-1)) // it's last
        {
            //cout << "Is last: " << "item = " << *it << " compared to " << *(strip.end()-1) << endl;
            result.push_back(strip.size()+1);
        }
        else
        {
            result.push_back(getPosition(strip, 0, strip.size()-1, *it));
        }
    }


    return result;
};
// {100, 50, 40, 20, 10}
int getPosition(const vector<int>& ranked, int begin, int end, const int& item)
{
    int middle;
    //cout << "Search position for item = " << item << " compared to " << ranked[begin] << " and " << ranked[end] << endl;
    if ((abs(begin - end)) == 1) // we have only to elemens and the element wasn't found we return the begin + 1 because it's alaways going to be between the two
    {
        //cout << "position found = " << begin+1 << endl;
        return begin+2; // adding two because we start at 0 and we loose a rank
    }

    if (ranked[begin] > ranked[end])
    {
        middle = begin + (end - begin)/2;
        if (item == ranked[middle])
        {
            //cout << "position found = " << middle << endl;
            return middle+1;
        }

        if (item > ranked[middle])
        {
            return getPosition(ranked, begin, middle, item);
        }

        if (item < ranked[middle])
        {
            return getPosition(ranked, middle, end, item);
        }
    }

    return -1;
}

vector<int> stripDups(const vector<int>& ranked)
{
    vector<int> result{}; 
    for (auto it = ranked.begin(); it != ranked.end(); ++it)
    {
        if (*it != *(it+1))
        {
            result.push_back(*it);
        }
    }
    return result;
}

int main() 
{
    //vector<int> rankedList = {295, 294, 291, 287, 287, 285, 285, 284, 283, 279, 277, 274, 274, 271, 270, 268, 268, 268, 264, 260, 259, 258, 257, 255, 252, 250, 244, 241, 240, 237, 236, 236, 231, 227, 227, 227, 226, 225, 224, 223, 216, 212, 200, 197, 196, 194, 193, 189, 188, 187, 183, 182, 178, 177, 173, 171, 169, 165, 143, 140, 137, 135, 133, 130, 130, 130, 128, 127, 122, 120, 116, 114, 113, 109, 106, 103, 99, 92, 85, 81, 69, 68, 63, 63, 63, 61, 57, 51, 47, 46, 38, 30, 28, 25, 22, 15, 14, 12, 6, 4};
    //vector<int> playerValues = {5, 5, 6, 14, 19, 20, 23, 25, 29, 29, 30, 30, 32, 37, 38, 38, 38, 41, 41, 44, 45, 45, 47, 59, 59, 62, 63, 65, 67, 69, 70, 72, 72, 76, 79, 82, 83, 90, 91, 92, 93, 98, 98, 100, 100, 102, 103, 105, 106, 107, 109, 112, 115, 118, 118, 121, 122, 122, 123, 125, 125, 125, 127, 128, 131, 131, 133, 134, 139, 140, 141, 143, 144, 144, 144, 144, 147, 150, 152, 155, 156, 160, 164, 164, 165, 165, 166, 168, 169, 170, 171, 172, 173, 174, 174, 180, 184, 187, 187, 188, 194, 197, 197, 197, 198, 201, 202, 202, 207, 208, 211, 212, 212, 214, 217, 219, 219, 220, 220, 223, 225, 227, 228, 229, 229, 233, 235, 235, 236, 242, 242, 245, 246, 252, 253, 253, 257, 257, 260, 261, 266, 266, 268, 269, 271, 271, 275, 276, 281, 282, 283, 284, 285, 287, 289, 289, 295, 296, 298, 300, 300, 301, 304, 306, 308, 309, 310, 316, 318, 318, 324, 326, 329, 329, 329, 330, 330, 332, 337, 337, 341, 341, 349, 351, 351, 354, 356, 357, 366, 369, 377, 379, 380, 382, 391, 391, 394, 396, 396, 400};
    //vector<int> rankedList = {997, 981, 957, 933, 930, 927, 926, 920, 916, 896, 887, 874, 863, 863, 858, 847, 815, 809, 803, 794, 789, 785, 783, 778, 764, 755, 751, 740, 737, 730, 691, 677, 652, 650, 587, 585, 583, 568, 546, 541, 540, 538, 531, 527, 506, 493, 457, 435, 430, 427, 422, 422, 414, 404, 400, 394, 387, 384, 374, 371, 369, 369, 368, 365, 363, 337, 336, 328, 325, 316, 314, 306, 282, 277, 230, 227, 212, 199, 179, 173, 171, 168, 136, 125, 124, 95, 92, 88, 85, 70, 68, 61, 60, 59, 44, 43, 28, 23, 13, 12};
    //vector<int> playerValues = {12, 20, 30, 32, 35, 37, 63, 72, 83, 85, 96, 98, 98, 118, 122, 125, 129, 132, 140, 144, 150, 164, 184, 191, 194, 198, 200, 220, 228, 229, 229, 236, 238, 246, 259, 271, 276, 281, 283, 287, 300, 302, 306, 307, 312, 318, 321, 325, 341, 341, 341, 344, 349, 351, 354, 356, 366, 369, 370, 379, 380, 380, 396, 405, 408, 417, 423, 429, 433, 435, 438, 441, 442, 444, 445, 445, 452, 453, 465, 466, 467, 468, 469, 471, 475, 482, 489, 491, 492, 493, 498, 500, 501, 504, 506, 508, 523, 529, 530, 539, 543, 551, 552, 556, 568, 569, 571, 587, 591, 601, 602, 606, 607, 612, 614, 619, 620, 623, 625, 625, 627, 638, 645, 653, 661, 662, 669, 670, 676, 684, 689, 690, 709, 709, 710, 716, 724, 726, 730, 731, 733, 737, 744, 744, 747, 757, 764, 765, 765, 772, 773, 774, 777, 787, 794, 796, 797, 802, 805, 811, 814, 819, 819, 829, 830, 841, 842, 847, 857, 857, 859, 860, 866, 872, 879, 882, 895, 900, 900, 903, 905, 915, 918, 918, 922, 925, 927, 928, 929, 931, 934, 937, 955, 960, 966, 974, 982, 988, 996, 996};
    vector<int> rankedList = {5, 2};
    vector<int> playerValues = {2, 1};
    vector<int> result = climbingLeaderboard(rankedList, playerValues);
    for (auto& item: result)
    {
        cout << item << endl;
    }
}