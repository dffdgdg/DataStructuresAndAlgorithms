#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;
// 1. Анализ времени выполнения простых алгоритмов

static int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

static int sumArray(int arr[], int n) 
{
    int sum = 0;
    for (int i = 0; i < n; i++) 
    {
        sum += arr[i];
    }
    return sum;
}

static bool isContainsNumber(int arr[], int n, int target) 
{
    for (int i = 0; i < n; i++) 
    {
        if (arr[i] == target) 
        {
            return true;
        }
    }
    return false;
}

// 2. Сравнение алгоритмов

static void bubbleSort(int arr[], int n) 
{
    bool swapped;
    for (int i = 0; i < n - 1; i++) 
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

static void insertionSort(int arr[], int n) 
{
    for (int i = 1; i < n; i++) 
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 3. Задачи для ICPC
// 3.1 Поиск второй по величине строки в массиве
// Вариант 1
static string findSecondLargestSorting(vector<string>& arr) 
{
    sort(arr.begin(), arr.end());
    return arr[arr.size() - 2];
}
// Вариант 2
static string findSecondLargestSinglePass(vector<string>& arr) 
{
    string first, second;
    for (const auto& str : arr) 
    {
        if (str > first) 
        {
            second = first;
            first = str;
        }
        else if (str > second && str != first) 
        {
            second = str;
        }
    }
    return second;
}

// 3.2 Проверка на палиндром
//Вариант 1
static bool isPalindromeTwoPointers(const string& s) 
{
    int left = 0, right = s.length() - 1;
    while (left < right) 
    {
        while (left < right && !isalnum(s[left])) left++;
        while (left < right && !isalnum(s[right])) right--;
        if (tolower(s[left]) != tolower(s[right])) return false;
        left++;
        right--;
    }
    return true;
}
//Вариант 2
static bool isPalindromeReverse(const string& s) 
{
    string filtered;
    for (char ch : s) 
    {
        if (isalnum(ch)) 
        {
            filtered.push_back(tolower(ch));
        }
    }
    string reversed(filtered.rbegin(), filtered.rend());
    return filtered == reversed;
}

// 3.3 Подсчет уникальных элементов в массиве
// Вариант 1
static int countUniqueUsingSet(const vector<int>& arr) 
{
    unordered_set<int> uniqueElements(arr.begin(), arr.end());
    return uniqueElements.size();
}

// Вариант 2
static int countUniqueWithSorting(vector<int>& arr) 
{
    if (arr.empty()) return 0;
    sort(arr.begin(), arr.end());
    int count = 1;
    for (int i = 1; i < arr.size(); i++) 
    {
        if (arr[i] != arr[i - 1]) 
        {
            count++;
        }
    }
    return count;
}

// 3.4 Поиск наименьшего отсутствующего положительного числа
// Вариант 1
static int findMissingPositiveUsingSet(const vector<int>& nums) 
{
    unordered_set<int> numSet(nums.begin(), nums.end());
    int missing = 1;
    while (numSet.count(missing)) 
    {
        missing++;
    }
    return missing;
}

// Вариант 2
static int findMissingPositiveWithSorting(vector<int>& nums) 
{
    sort(nums.begin(), nums.end());
    int missing = 1;
    for (int num : nums) 
    {
        if (num == missing) 
        {
            missing++;
        }
    }
    return missing;
}

int main() 
{
    setlocale(LC_ALL, "Russian");

    int arr[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Содержит ли массив число 5? O(n): " << (isContainsNumber(arr, n, 5) ? "Да" : "Нет") << endl;
    cout << "Максимальный элемент O(n): " << findMax(arr, n) << endl;
    cout << "Сумма элементов O(n): " << sumArray(arr, n) << endl;
    cout << endl;

    int arr2[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    auto startBubble = high_resolution_clock::now();
    bubbleSort(arr2, n2);
    auto endBubble = high_resolution_clock::now();
    duration<double> bubbleTime = endBubble - startBubble;

    for (int i = 0; i < n2; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl << "Время выполнения пузырьковой сортировки О(n^2):" << bubbleTime.count() << " секунд" << endl;

    int arr3[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    auto startInsertion = high_resolution_clock::now();
    insertionSort(arr3, n3);
    auto endInsertion = high_resolution_clock::now();
    duration<double> insertionTime = endInsertion - startInsertion;

    cout << "Время выполнения отсортированной сортировки O(n^2):" << insertionTime.count() << " секунд" << endl;

    if (bubbleTime > insertionTime) {
        cout << "Сортировка вставками быстрее на " << (bubbleTime - insertionTime).count() << " секунд" << endl;
    }
    else {
        cout << "Пузырьковая сортировка быстрее на " << (insertionTime - bubbleTime).count() << " секунд" << endl;
    }
    cout << endl;
    vector<string> strings = { "5", "apple", "banana", "cherry", "date", "elderberry" };
    cout << "Вторая по величине строка (Вариант 1) O(n log n): " << findSecondLargestSorting(strings) << endl;
    cout << "Вторая по величине строка (Вариант 2) O(n): " << findSecondLargestSinglePass(strings) << endl;
    cout << endl;
    string palindromeTest = "A man, a plan, a canal, Panama";
    cout << "Палиндром (Вариант 1) O(n): " << (isPalindromeTwoPointers(palindromeTest) ? "Да" : "Нет") << endl;
    cout << "Палиндром (Вариант 2) O(n): " << (isPalindromeReverse(palindromeTest) ? "Да" : "Нет") << endl;
    cout << endl;
    vector<int> uniqueTest = { 1, 2, 2, 3, 4, 4, 5 };
    cout << "Количество уникальных элементов (Вариант 1) O(n): " << countUniqueUsingSet(uniqueTest) << endl;
    cout << "Количество уникальных элементов (Вариант 2) O(n log n): " << countUniqueWithSorting(uniqueTest) << endl;
    cout << endl;
    vector<int> missingPositiveTest = { 1, 2, 0, -1, 3 };
    cout << "Наименьшее отсутствующее положительное число (Вариант 1) O(n): " << findMissingPositiveUsingSet(missingPositiveTest) << endl;
    cout << "Наименьшее отсутствующее положительное число (Вариант 2) O(n log n): " << findMissingPositiveWithSorting(missingPositiveTest) << endl;
    return 0;
}
