// ArcadiaEngine.cpp - STUDENT TEMPLATE
// TODO: Implement all the functions below according to the assignment requirements

#include "ArcadiaEngine.h"
#include <algorithm>
#include <queue>
#include <numeric>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>

using namespace std;

// =========================================================
// HELPER UTILITY FUNCTIONS
// =========================================================

namespace HelperUtils {
    
    // --- String Helpers ---
    
    // Check if string contains only digits
    bool isAllDigits(const string& s) {
        if (s.empty()) return false;
        for (size_t i = 0; i < s.length(); i++) {
            if (s[i] < '0' || s[i] > '9') {
                return false;
            }
        }
        return true;
    }
    
    // Check if string is a valid integer (including negative)
    bool isInteger(const string& s) {
        if (s.empty()) return false;
        size_t start = 0;
        if (s[0] == '-' || s[0] == '+') {
            if (s.length() == 1) return false;
            start = 1;
        }
        for (size_t i = start; i < s.length(); i++) {
            if (s[i] < '0' || s[i] > '9') {
                return false;
            }
        }
        return true;
    }
    
    // Convert integer to string manually (handles INT_MIN correctly)
    string intToString(int num) {
        if (num == 0) return "0";
        
        bool negative = num < 0;
        // Convert to unsigned to avoid overflow with INT_MIN
        unsigned int absNum;
        if (negative) {
            absNum = (unsigned int)(-(num + 1)) + 1;  // Avoid overflow
        } else {
            absNum = (unsigned int)num;
        }
        
        string result = "";
        while (absNum > 0) {
            result = char('0' + (absNum % 10)) + result;
            absNum /= 10;
        }
        
        if (negative) result = "-" + result;
        return result;
    }
    
    // Convert long long to string manually (handles LLONG_MIN correctly)
    string longToString(long long num) {
        if (num == 0) return "0";
        
        bool negative = num < 0;
        // Convert to unsigned to avoid overflow with LLONG_MIN
        unsigned long long absNum;
        if (negative) {
            absNum = (unsigned long long)(-(num + 1)) + 1;  // Avoid overflow
        } else {
            absNum = (unsigned long long)num;
        }
        
        string result = "";
        while (absNum > 0) {
            result = char('0' + (absNum % 10)) + result;
            absNum /= 10;
        }
        
        if (negative) result = "-" + result;
        return result;
    }
    
    // Convert string to integer manually
    int stringToInt(const string& s) {
        if (s.empty()) return 0;
        
        int result = 0;
        size_t i = 0;
        bool negative = false;
        
        if (s[0] == '-') {
            negative = true;
            i = 1;
        } else if (s[0] == '+') {
            i = 1;
        }
        
        for (; i < s.length(); i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                result = result * 10 + (s[i] - '0');
            }
        }
        
        return negative ? -result : result;
    }
    
    // Convert decimal number to binary string
    string decimalToBinary(long long num) {
        if (num == 0) return "0";
        
        string binary = "";
        while (num > 0) {
            binary = char('0' + (num % 2)) + binary;
            num /= 2;
        }
        return binary;
    }
    
    // Convert binary string to decimal
    long long binaryToDecimal(const string& binary) {
        long long result = 0;
        long long power = 1;
        
        for (int i = binary.length() - 1; i >= 0; i--) {
            if (binary[i] == '1') {
                result += power;
            }
            power *= 2;
        }
        return result;
    }
    
    // Add two binary strings and return result as binary string
    string addBinaryStrings(const string& a, const string& b) {
        string result = "";
        int carry = 0;
        int i = a.length() - 1;
        int j = b.length() - 1;
        
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += (a[i--] - '0');
            if (j >= 0) sum += (b[j--] - '0');
            
            result = char('0' + (sum % 2)) + result;
            carry = sum / 2;
        }
        
        return result.empty() ? "0" : result;
    }
    
    // --- Array/Math Helpers ---
    
    // Check if all elements in array are positive
    bool allPositive(const int* arr, int size) {
        for (int i = 0; i < size; i++) {
            if (arr[i] <= 0) return false;
        }
        return true;
    }
    
    // Check if all elements in array are non-negative
    bool allNonNegative(const int* arr, int size) {
        for (int i = 0; i < size; i++) {
            if (arr[i] < 0) return false;
        }
        return true;
    }
    
    // Find minimum value in array
    int findMin(const int* arr, int size) {
        if (size <= 0) return INT_MAX;
        int minVal = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] < minVal) minVal = arr[i];
        }
        return minVal;
    }
    
    // Find maximum value in array
    int findMax(const int* arr, int size) {
        if (size <= 0) return INT_MIN;
        int maxVal = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] > maxVal) maxVal = arr[i];
        }
        return maxVal;
    }
    
    // Calculate sum of array elements
    long long arraySum(const int* arr, int size) {
        long long sum = 0;
        for (int i = 0; i < size; i++) {
            sum += arr[i];
        }
        return sum;
    }
    
    // Swap two integers
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
    
    // Swap two long long values
    void swapLong(long long& a, long long& b) {
        long long temp = a;
        a = b;
        b = temp;
    }
    
    // --- Prime Number Helpers (useful for hash table sizing) ---
    
    // Check if a number is prime
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }
    
    // Find next prime number >= n (useful for hash table size)
    int nextPrime(int n) {
        if (n <= 2) return 2;
        
        int candidate = (n % 2 == 0) ? n + 1 : n;
        
        while (!isPrime(candidate)) {
            candidate += 2;
        }
        return candidate;
    }
    
    // --- Hash Functions (for Double Hashing) ---
    
    // Primary hash function
    int hash1(int key, int tableSize) {
        return abs(key) % tableSize;
    }
    
    // Secondary hash function for double hashing
    // Returns a value between 1 and tableSize-1
    int hash2(int key, int tableSize) {
        // Use a prime number smaller than table size
        int prime = tableSize - 1;
        while (!isPrime(prime) && prime > 1) {
            prime--;
        }
        return prime - (abs(key) % prime);
    }
    
    // --- Random Number Generator (for Skip List level generation) ---
    
    // Generate random level for skip list (geometric distribution)
    // maxLevel: maximum level allowed
    // probability: typically 0.5 (return higher level with 50% chance)
    int randomLevel(int maxLevel) {
        int level = 1;
        // Use coin flip simulation: 50% chance to go to next level
        while (level < maxLevel && (rand() % 2 == 0)) {
            level++;
        }
        return level;
    }
    
    // --- Comparison Helpers ---
    
    // Compare two integers (for sorting)
    // Returns: -1 if a < b, 0 if a == b, 1 if a > b
    int compareInt(int a, int b) {
        if (a < b) return -1;
        if (a > b) return 1;
        return 0;
    }
    
    // Compare two long long values
    int compareLong(long long a, long long b) {
        if (a < b) return -1;
        if (a > b) return 1;
        return 0;
    }
    
    // --- Memory Helpers ---
    
    // Safe integer division with ceiling
    int ceilDiv(int numerator, int denominator) {
        if (denominator == 0) return 0;
        return (numerator + denominator - 1) / denominator;
    }
    
    // Calculate absolute value safely
    int absoluteValue(int n) {
        return (n < 0) ? -n : n;
    }
    
    long long absoluteValueLong(long long n) {
        return (n < 0) ? -n : n;
    }
    
    // --- Validation Helpers ---
    
    // Check if index is valid for array
    bool isValidIndex(int index, int size) {
        return index >= 0 && index < size;
    }
    
    // Check if value is power of 2
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }
    
    // Get next power of 2 >= n
    int nextPowerOfTwo(int n) {
        if (n <= 1) return 1;
        n--;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        return n + 1;
    }
    
    // --- GCD and LCM (useful for various algorithms) ---
    
    // Greatest Common Divisor
    int gcd(int a, int b) {
        a = absoluteValue(a);
        b = absoluteValue(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
    // Least Common Multiple
    int lcm(int a, int b) {
        if (a == 0 || b == 0) return 0;
        return absoluteValue(a * b) / gcd(a, b);
    }

} // namespace HelperUtils

// =========================================================
// PART A: DATA STRUCTURES (Concrete Implementations)
// =========================================================

// --- 1. PlayerTable (Double Hashing) ---
#define TableSize 101
struct Player {
    int playerID;
    string name;
    bool isOccupied;

    Player() : playerID(-1), name(""), isOccupied(false) {}

    Player(int id, const string& n, bool occupied)
            : playerID(id), name(n), isOccupied(occupied) {}
};

class ConcretePlayerTable : public PlayerTable {
private:
    void printTable() {
        cout << "Hash Table Contents:\n";
        for (int i = 0; i < TableSize; i++) {
            cout << "Index " << i << ": ";
            if (hashTable[i].isOccupied) {
                cout << "(" << hashTable[i].playerID << ", "
                     << hashTable[i].name << ")";
            } else {
                cout << "Empty";
            }
            cout << endl;


        }
        cout << endl;
    }

    vector<Player> hashTable;
    const double A = 0.6180339887;

    // 1st hash func
    int h1(int key) { //floor( m( kA mod 1 ) )
        double frac = fmod(key * A, 1.0);
        return int(floor(TableSize * frac));
    }

    // 2nd hash func
    int h2(int key) { //1+(k mod(m−1)) 1->100
        return 1 + (key % (TableSize - 1));
    }
public:
    ConcretePlayerTable():hashTable(TableSize) {}

    void insert(int playerID, string name) override {
        int h1Index = h1(playerID);
        int h2step = h2(playerID);
        bool inserted = false;

        for (int i = 0; i < TableSize; i++) {
            if (i>=1) {cout<<"collision 🙂🙂🙂🙂🙂🙂🙂🙂🙂🙂🙂🙂🙂🙂🙂🙂"<<endl;
                cout <<playerID<<endl;}
            int index = (h1Index + i * h2step) % TableSize;

            if (!hashTable[index].isOccupied) {
                hashTable[index] = {playerID, name, true};
                inserted = true;
                break;
            }
        }

        if (!inserted) {
            cout << "Table is Full" << endl;
        }
        printTable();
    }

    string search(int playerID) override {
        //printTable();
        int h1Index = h1(playerID);
        int h2step = h2(playerID);

        for (int i = 0; i < TableSize; i++) {
            int index = (h1Index + i * h2step) % TableSize;

            if (!hashTable[index].isOccupied) {
                return ""; // Player not found
            }
            if (hashTable[index].playerID == playerID) {
                return hashTable[index].name;
            }
        }
        return "";
    }
};

// --- 2. Leaderboard (Skip List) ---

class ConcreteLeaderboard : public Leaderboard {
private:
    // TODO: Define your skip list node structure and necessary variables
    // Hint: You'll need nodes with multiple forward pointers
    // Use HelperUtils::randomLevel() to determine node height

public:
    ConcreteLeaderboard() {
        // TODO: Initialize your skip list
    }

    void addScore(int playerID, int score) override {
        // TODO: Implement skip list insertion
        // Remember to maintain descending order by score
    }

    void removePlayer(int playerID) override {
        // TODO: Implement skip list deletion
    }

    vector<int> getTopN(int n) override {
        // TODO: Return top N player IDs in descending score order
        return {};
    }
};

// --- 3. AuctionTree (Red-Black Tree) ---

class ConcreteAuctionTree : public AuctionTree {
private:
    // TODO: Define your Red-Black Tree node structure
    // Hint: Each node needs: id, price, color, left, right, parent pointers

public:
    ConcreteAuctionTree() {
        // TODO: Initialize your Red-Black Tree
    }

    void insertItem(int itemID, int price) override {
        // TODO: Implement Red-Black Tree insertion
        // Remember to maintain RB-Tree properties with rotations and recoloring
    }

    void deleteItem(int itemID) override {
        // TODO: Implement Red-Black Tree deletion
        // This is complex - handle all cases carefully
    }
};

// =========================================================
// PART B: INVENTORY SYSTEM (Dynamic Programming)
// =========================================================

int InventorySystem::optimizeLootSplit(int n, vector<int>& coins) {
    // TODO: Implement partition problem using DP
    // Goal: Minimize |sum(subset1) - sum(subset2)|
    // Hint: Use subset sum DP to find closest sum to total/2
    // You can use HelperUtils::arraySum() to calculate total sum
    int total = 0;
    for (int c : coins)
        total += c;

    int target = total / 2;

    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int c : coins)
    {
        for (int s = target; s >= c; s--)
        {
            if (dp[s - c])
                dp[s] = true;
        }
    }

    int best = 0;
    for (int s = target; s >= 0; s--)
    {
        if (dp[s])
        {
            best = s;
            break;
        }
    }

    int other = total - best;
    return abs(other - best);
}

int InventorySystem::maximizeCarryValue(int capacity, vector<pair<int, int>>& items) {
    // TODO: Implement 0/1 Knapsack using DP
    // items = {weight, value} pairs
    // Return maximum value achievable within capacity
    // Use HelperUtils::findMax() if needed
    int R = items.size();  //total rows
    int C = capacity;  //total columns
    int dp[R + 1][C + 1];

    for (int r = 1; r <= R; r++)
    {
        int weight = items[r - 1].first;
        int value = items[r - 1].second;

        for (int c = 1; c <= C; c++)
        {
            dp[r][c] = dp[r - 1][c];

            if (c >= weight)
            {
                dp[r][c] = max(dp[r][c], dp[r - 1][c - weight] + value);
            }
        }
    }

    return dp[R][C];
}

long long InventorySystem::countStringPossibilities(string s) {
    // TODO: Implement string decoding DP
    // Rules: "uu" can be decoded as "w" or "uu"
    //        "nn" can be decoded as "m" or "nn"
    // Count total possible decodings
    const long long MOD = 1e9 + 7;
    int n = s.size();

    map<string, long long> dp;
    dp[""] = 1LL;
    dp["n"] = 1LL;
    dp["u"] = 1LL;
    dp["nn"] = 2LL;
    dp["uu"] = 2LL;

    //------------------------------------------

    queue<char> q;
    for (int i = 0 ; i < n; i++)
    {
        q.push(s[i]);
    }

    long long count = 1;   

    while (!q.empty())
    {
        char ch1 = q.front();
        q.pop();

        if (q.empty())
        {
            string single = "";
            single += ch1;

            if (dp.find(single) != dp.end())
                count *= dp[single];
            else
                count *= dp[""] ;

            break;
        }

        //------------------------------------------
        char ch2 = q.front();
        
        string comb = "";
        comb += ch1;
        comb += ch2;

        if (dp.find(comb) != dp.end())
        {
            count *= dp[comb];
            q.pop();
        }
        else
        {
            string single = "";
            single += ch1;

            if (dp.find(single) != dp.end())
                count *= dp[single];
            else
                count *= dp[""] ;
        }
    }

    return count % MOD;
}

// =========================================================
// PART C: WORLD NAVIGATOR (Graphs)
// =========================================================

bool WorldNavigator::pathExists(int n, vector<vector<int>>& edges, int source, int dest) {
    // TODO: Implement path existence check using BFS or DFS
    // edges are bidirectional
    // Use HelperUtils::isValidIndex() for bounds checking
    return false;
}

long long WorldNavigator::minBribeCost(int n, int m, long long goldRate, long long silverRate,
    vector<vector<int>>& roadData) {
    // TODO: Implement Minimum Spanning Tree (Kruskal's or Prim's)
    // roadData[i] = {u, v, goldCost, silverCost}
    // Total cost = goldCost * goldRate + silverCost * silverRate
    // Return -1 if graph cannot be fully connected
    return -1;
}

string WorldNavigator::sumMinDistancesBinary(int n, vector<vector<int>>& roads) {
    // TODO: Implement All-Pairs Shortest Path (Floyd-Warshall)
    // Sum all shortest distances between unique pairs (i < j)
    // Return the sum as a binary string
    // Hint: Handle large numbers carefully
    // Use HelperUtils::decimalToBinary() to convert result
    // Use HelperUtils::addBinaryStrings() if you need to add large numbers
    return "0";
}

// =========================================================
// PART D: SERVER KERNEL (Greedy)
// =========================================================

int ServerKernel::minIntervals(vector<char>& tasks, int n) {
    // TODO: Implement task scheduler with cooling time
    // Same task must wait 'n' intervals before running again
    // Return minimum total intervals needed (including idle time)
    // Hint: Use greedy approach with frequency counting
    // Use HelperUtils::findMax() to find most frequent task
    return 0;
}

// =========================================================
// FACTORY FUNCTIONS (Required for Testing)
// =========================================================

extern "C" {
    PlayerTable* createPlayerTable() {
        return new ConcretePlayerTable();
    }

    Leaderboard* createLeaderboard() {
        return new ConcreteLeaderboard();
    }

    AuctionTree* createAuctionTree() {
        return new ConcreteAuctionTree();
    }
}

// =========================================================
// MAIN FUNCTION (For Testing)
// =========================================================

int main() {
    cout << "Arcadia Engine - Student Implementation" << endl;
    cout << "This is a template. Implement the TODO functions." << endl;
    
    // Test helper functions
    cout << "\n=== Testing Helper Functions ===" << endl;
    
    // String helpers
    cout << "isInteger('123'): " << HelperUtils::isInteger("123") << endl;
    cout << "isInteger('-456'): " << HelperUtils::isInteger("-456") << endl;
    cout << "isInteger('abc'): " << HelperUtils::isInteger("abc") << endl;
    
    // Conversion helpers
    cout << "intToString(12345): " << HelperUtils::intToString(12345) << endl;
    cout << "stringToInt('678'): " << HelperUtils::stringToInt("678") << endl;
    
    // Binary helpers
    cout << "decimalToBinary(42): " << HelperUtils::decimalToBinary(42) << endl;
    cout << "binaryToDecimal('101010'): " << HelperUtils::binaryToDecimal("101010") << endl;
    cout << "addBinaryStrings('1010', '1101'): " << HelperUtils::addBinaryStrings("1010", "1101") << endl;
    
    // Prime helpers
    cout << "isPrime(17): " << HelperUtils::isPrime(17) << endl;
    cout << "nextPrime(100): " << HelperUtils::nextPrime(100) << endl;
    
    // Hash functions
    int tableSize = 101;
    int key = 54321;
    cout << "hash1(" << key << ", " << tableSize << "): " << HelperUtils::hash1(key, tableSize) << endl;
    cout << "hash2(" << key << ", " << tableSize << "): " << HelperUtils::hash2(key, tableSize) << endl;
    
    cout << "\n=== Helper functions ready for use ===" << endl;
    
    return 0;
}