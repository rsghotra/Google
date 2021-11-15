#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;


class MedianOfAStream {
  private:
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<>> minHeap;
  public:
    double CalculateMedian() { //o(1)
      if(minHeap.size() == maxHeap.size()) {
        return (minHeap.top()/2.0 + maxHeap.top()/2.0);
      }
      return maxHeap.top();
    }
    void InsertNum(int num) { //o(logn); space = o(n) as we are saving all the numbers;
      if(maxHeap.empty() || num <= maxHeap.top()) {
        maxHeap.push(num);
      } else {
        minHeap.push(num);
      }

      if(maxHeap.size() > minHeap.size() + 1) {
        minHeap.push(maxHeap.top());
        maxHeap.pop();
      } else if(minHeap.size() > maxHeap.size()) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
      }
    } 
};

void StreamMedian() {
    MedianOfAStream medianOfAStream;
    medianOfAStream.InsertNum(3);
    medianOfAStream.InsertNum(1);
    cout << "The median is: " << medianOfAStream.CalculateMedian() << endl;
    medianOfAStream.InsertNum(5);
    cout << "The median is: " << medianOfAStream.CalculateMedian() << endl;
    medianOfAStream.InsertNum(4);
    cout << "The median is: " << medianOfAStream.CalculateMedian() << endl;
}


struct CapitalCompare {
  bool operator()(const pair<int, int>& x, const pair<int, int>& y) {
    return x.first > y.first;
  }
};


struct ProfitCompare {
  bool operator()(const pair<int, int>& x, const pair<int, int>& y) {
    return x.first < y.first;
  }
};

int MaximumCapital(const vector<int>& projects, const vector<int>& profits, int initialCapital, int numProjects) {
  priority_queue<pair<int, int>, vector<pair<int,int>>, CapitalCompare> minCapitalHeap;
  priority_queue<pair<int, int>, vector<pair<int, int>>, ProfitCompare> maxProfitHeap;

  //push project capital to minHeap
  for(int i = 0; i < projects.size(); i++) {
    minCapitalHeap.push(make_pair(projects[i], i));
  }

  int availableCapital = initialCapital;
  for(int i = 0; i < numProjects; i++) {
    while(!minCapitalHeap.empty() && minCapitalHeap.top().first <= availableCapital) {
      int projectIndex = minCapitalHeap.top().second;
      minCapitalHeap.pop();
      maxProfitHeap.push(make_pair(profits[projectIndex], projectIndex));
    }

    if(maxProfitHeap.empty()) {
      break;
    }

    availableCapital += maxProfitHeap.top().first;
    maxProfitHeap.pop();
  }

  return availableCapital;

}

void MaximizeCapital() {
  int result =
        MaximumCapital(vector<int>{0, 1, 2}, vector<int>{1, 2, 3}, 2, 1);
    cout << "Maximum capital: " << result << endl;
    result =
        MaximumCapital(vector<int>{0, 1, 2, 3}, vector<int>{1, 2, 3, 5}, 3, 0);
    cout << "Maximum capital: " << result << endl;
}

template<typename T, class Container = vector<T>, class Compare = less<typename Container::value_type>>
class priority_queue_with_remove: public priority_queue<T, Container, Compare> {
public:
  bool remove(const T& valToRemove) {
    auto itr = std::find(this->c.begin(), this->c.end(), valToRemove);
    if(itr == this->c.end()) {
      return false;
    }
    this->c.erase(itr);
    std::make_heap(this->c.begin(), this->c.end(), this->comp);
    return true;
  }
};

class SlidingWindowMedian {
private:
    vector<double> result;
    priority_queue_with_remove<int> maxHeap;
    priority_queue_with_remove<int, vector<int>, greater<>> minHeap;
public:
    virtual double CalculateMedian() {
      if(maxHeap.size() == minHeap.size()) {
        return (maxHeap.top()/2.0) + (minHeap.top()/2.0);
      }
      return maxHeap.top();
    }
    virtual void RebalanceHeaps() {
      if(maxHeap.size() > minHeap.size() + 1) {
        minHeap.push(maxHeap.top());
        maxHeap.pop();
      } else if(minHeap.size() > maxHeap.size()) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
      }
    }
    virtual vector<double> FindSlidingWindowMedian(const vector<int>& nums, int k) {
      int windowStart = 0;
      for(int windowEnd = 0; windowEnd < nums.size(); windowEnd++) {
        if(maxHeap.empty() || nums[windowEnd] <= maxHeap.top()) {
          maxHeap.push(nums[windowEnd]);
        } else {
          minHeap.push(nums[windowEnd]);
        }
        RebalanceHeaps();
        if(windowEnd - windowStart + 1 >= k) {
          result.push_back(CalculateMedian());
          double eleToRemove = nums[windowStart];
          if(eleToRemove <= maxHeap.top()) {
            maxHeap.remove(eleToRemove);
          } else {
            minHeap.remove(eleToRemove);
          }
          RebalanceHeaps();
          windowStart++;
        }
      }
      return result;
    }
};

void Slm() {
  SlidingWindowMedian slm;
  vector<double> result = slm.FindSlidingWindowMedian(vector<int>{1, 2, -1, 3, 5}, 2);
  cout << "Sliding window medians are: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;

  slm = SlidingWindowMedian();
  result = slm.FindSlidingWindowMedian(vector<int>{1, 2, -1, 3, 5}, 3);
  cout << "Sliding window medians are: ";
  for (auto num : result) {
    cout << num << " ";
  }
}

class Interval {
public:
  int start;
  int end;
public:
  Interval(int s, int e) {
    this->start = s;
    this->end = e;
  }
};

struct StartCompare {
  bool operator()(const pair<Interval, int> x, const pair<Interval, int> y) {
    return x.first.start < y.first.start;
  }
};

struct EndCompare {
  bool operator()(const pair<Interval, int> x, const pair<Interval, int> y) {
    return x.first.end < y.first.end;
  }
};

class NextInterval {
private:
  priority_queue<pair<Interval, int>, vector<pair<Interval, int>>, StartCompare> maxStartHeap;
  priority_queue<pair<Interval, int>, vector<pair<Interval, int>>, EndCompare> maxEndHeap;
public:
  virtual vector<int> FindNextIntervals(const vector<Interval>& intervals) {
    int n = intervals.size();
    vector<int> result(n, -1);
    for(int i = 0; i < intervals.size(); i++) {
      maxStartHeap.push(make_pair(intervals[i], i));
      maxEndHeap.push(make_pair(intervals[i], i));
    }

    while(!maxEndHeap.empty()) {
      auto topEnd = maxEndHeap.top();
      maxEndHeap.pop();
      pair<Interval, int> topStart = pair<Interval, int>({-1, -1}, -1);
      result[topEnd.second] = -1;
      while(!maxStartHeap.empty() && maxStartHeap.top().first.start >= topEnd.first.end) {
        topStart = maxStartHeap.top();
        maxStartHeap.pop();
      }
      result[topEnd.second] = topStart.second;
      //put the interval back as it could be the next interval of other intervals;
      maxStartHeap.push(topStart);
    }
    return result;
  }
};


void FindNextInterval() {
  vector<Interval> intervals = {{2, 3}, {3, 4}, {5, 6}};
  NextInterval nextInterval;
  vector<int> result = nextInterval.FindNextIntervals(intervals);
  cout << "\nNext interval indices are: ";
  for (auto index : result) {
    cout << index << " ";
  }
  cout << endl;

  intervals = {{3, 4}, {1, 5}, {4, 6}};
  result = nextInterval.FindNextIntervals(intervals);
  cout << "Next interval indices are: ";
  for (auto index : result) {
    cout << index << " ";
  }
}

struct ValCompare {
  bool operator()(const int& x, const int& y) {
    return x > y;
  }
};

vector<int> FindKLargest(const vector<int>& nums, int k) {
  if(k > nums.size()) {
    return {};
  }
  vector<int> minHeap(nums.begin(), nums.begin() + k);
  make_heap(minHeap.begin(), minHeap.end(), ValCompare());
  for(int i = k; i < nums.size(); i++) {
    if(nums[i] > minHeap.front()) {
      pop_heap(minHeap.begin(), minHeap.end(), ValCompare());
      minHeap.pop_back();
      minHeap.push_back(nums[i]);
      push_heap(minHeap.begin(), minHeap.end(), ValCompare());
    }
  }
  return minHeap;
}

void FindKLargest() {
  vector<int> result = FindKLargest(vector<int>{3, 1, 5, 12, 2, 11}, 3);
  cout << "Here are the top K numbers: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;

  result = FindKLargest(vector<int>{5, 12, 11, -1, 12}, 3);
  cout << "Here are the top K numbers: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;
}


int FindKthSmallest(const vector<int>& nums, int k) {
  priority_queue<int> maxHeap;
  for(int i = 0; i < k; i++) {
    maxHeap.push(nums[i]);
  }

  for(int i = k; i < nums.size(); i++) {
    if(nums[i] < maxHeap.top()) {
      maxHeap.pop();
      maxHeap.push(nums[i]);
    }
  }
  return maxHeap.top();
}

void FindKthSmallest() {
  int result = FindKthSmallest(vector<int>{1, 5, 12, 2, 11, 5}, 3);
  cout << "Kth smallest number is: " << result << endl;

  // since there are two 5s in the input array, our 3rd and 4th smallest numbers should be a '5'
  result = FindKthSmallest(vector<int>{1, 5, 12, 2, 11, 5}, 4);
  cout << "Kth smallest number is: " << result << endl;

  result = FindKthSmallest(vector<int>{5, 12, 11, -1, 12}, 3);
  cout << "Kth smallest number is: " << result << endl;
}


struct DistCompare {
  bool operator() (const vector<int>& point1, const vector<int>& point2) {
      int dist1 = point1[0]*point1[0] + point1[1]*point1[1];
      int dist2 = point2[0]*point2[0] + point2[1]*point2[1];
      return dist1 < dist2;
  }
};

vector<vector<int>> FindKClosestPoints(const vector<vector<int>>& points, int k) {
  vector<vector<int>> maxHeap(points.begin(), points.begin() + k);
  make_heap(maxHeap.begin(), maxHeap.end(), DistCompare());
  for(int i = k; i < points.size(); i++) {
    if((points[i][0]*points[i][0] + points[i][1]*points[i][1]) < (maxHeap.front()[0]*maxHeap.front()[0] + maxHeap.front()[1]*maxHeap.front()[1])) {
      pop_heap(maxHeap.begin(), maxHeap.end(), DistCompare());
      maxHeap.pop_back();
      maxHeap.push_back(points[i]);
      push_heap(maxHeap.begin(), maxHeap.end(), DistCompare());
    }
  }
  return maxHeap;
}


void ClosestDistanceFromOrigin() {
  vector<vector<int>> points = FindKClosestPoints({{1, 3}, {3, 4}, {2, -1}}, 2);
  cout << "Here are the k points closest the origin: ";
  for (auto p : points) {
    cout << "[" << p[0] << " , " << p[1] << "] ";
  }
  cout << endl;
}

int ConnectRopes(const vector<int>& ropes) {
  priority_queue<int, vector<int>, greater<>> minHeap;
  for(auto rope: ropes) {
    minHeap.push(rope);
  }
  int total_cost = 0;
  int cost_of_two_ropes = 0;
  while(minHeap.size() > 1) {
    cost_of_two_ropes = minHeap.top();
    minHeap.pop();
    cost_of_two_ropes += minHeap.top();
    minHeap.pop();
    total_cost += cost_of_two_ropes;
    minHeap.push(cost_of_two_ropes); //temp has cost of last two ropes; while cost represent total cost;
  }
  return total_cost;
}


void ConnectRopes() {
  int result = ConnectRopes(vector<int>{1, 3, 11, 5});
  cout << "Minimum cost to connect ropes: " << result << endl;
  result = ConnectRopes(vector<int>{3, 4, 5, 6});
  cout << "Minimum cost to connect ropes: " << result << endl;
  result = ConnectRopes(vector<int>{1, 3, 11, 5, 2});
  cout << "Minimum cost to connect ropes: " << result << endl;
}

struct FrequencyCompare {
  bool operator()(const pair<int, int>& x, const pair<int, int>& y) {
    return x.second > y.second;
  }
};
struct CharFrequencyCompare {
  bool operator()(const pair<char, int>& x, const pair<char, int>& y) {
    return x.second < y.second;
  }
};

vector<int> TopKFrequentNums(const vector<int>& nums, int k) {
  unordered_map<int, int> frequencies;
  priority_queue<pair<int, int>, vector<pair<int, int>>, FrequencyCompare> minHeap;
  for(auto& num: nums) {
    frequencies[num]++;
  }

  for(auto entry: frequencies) {
    if(minHeap.empty() || minHeap.size() < k) {
      minHeap.push(entry);
    } else if(entry.second > minHeap.top().second) {
      minHeap.pop();
      minHeap.push(entry);
    }
  }
  vector<int> result;
  while(!minHeap.empty()) {
    auto entry = minHeap.top();
    minHeap.pop();
    result.push_back(entry.first);
  }
  return result;
}


void TopKFrequentNums() {
  vector<int> result =
  TopKFrequentNums(vector<int>{1, 3, 5, 12, 11, 12, 11}, 2);
  cout << "Here are the K frequent numbers: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;

  result = TopKFrequentNums(vector<int>{5, 12, 11, 3, 11}, 2);
  cout << "Here are the K frequent numbers: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;
}

struct CharCompare {
  bool operator()(const pair<char, int>& x, const pair<char, int>& y) {
    return x.second < y.second;
  }
};

string FrequencySort(const string& input) {
  string result = "";
  unordered_map<char, int> frequencies;
  for(char ch: input) {
    frequencies[ch]++;
  }
  priority_queue<pair<char, int>, vector<pair<char, int>>, CharCompare> maxHeap;
  for(auto entry: frequencies) {
    maxHeap.push(entry);
  }
  while(maxHeap.empty() == false) {
    auto entry = maxHeap.top();
    maxHeap.pop();
    while(entry.second > 0) {
      result += entry.first;
      entry.second--;
    }
  }
  return result;
}


void FrequencySort() {
  string result = FrequencySort("Programming");
  cout << "Here is the given string after sorting characters by frequency: " << result << endl;

  result = FrequencySort("abcbab");
  cout << "Here is the given string after sorting characters by frequency: " << result << endl;
}

class KthLargestNumberInStream {
  priority_queue<int, vector<int>, greater<>> minHeap;
  int k;
public:
  KthLargestNumberInStream(const vector<int>& stream, int k) { //nlogk
    this->k = k;
    for(int i = 0; i < stream.size(); i++) {
      add(stream[i]);
    }
  }

  int add(int num) { //logK
    minHeap.push(num);
    if(minHeap.size() > k) {
      minHeap.pop();
    }
    return minHeap.top();
  }
};

void KthLargestNumberStream() {
    KthLargestNumberInStream kthLargestNumber({3, 1, 5, 12, 2, 11}, 4);
    cout << "4th largest number is: " << kthLargestNumber.add(6) << endl;
    cout << "4th largest number is: " << kthLargestNumber.add(13) << endl;
    cout << "4th largest number is: " << kthLargestNumber.add(4) << endl;
}

int BinarySearch(const vector<int>& nums, int num) {
  int start = 0;
  int end = nums.size() - 1;
  while(start <= end) {
    int mid = start + (end - start)/2;
    if(nums[mid] == num) {
      return mid;
    } else if(nums[mid] > num) {
      end = mid - 1;
    } else {
      start = mid + 1;
    }
  }
  if(start == nums.size()) {
    start = start -1;
  }
  return start;
}

vector<int> KClosestNumbers(const vector<int>& nums, int k, int X) {
  int index = BinarySearch(nums, X);
  int leftPtr = index;
  int rightPtr = index + 1;
  deque<int> result;
  vector<int> movedResult;
  for(int i = 0; i < k; i++) {
    if(leftPtr >= 0 && rightPtr <= nums.size() - 1) {
      if(abs(nums[leftPtr] - X) <= abs(nums[rightPtr] - X)) {
        result.push_front(nums[leftPtr]); //cool trick
        leftPtr--;
      } else {
        result.push_back(nums[rightPtr]);
        rightPtr++;
      }
    } else if(leftPtr >= 0) {
      result.push_front(nums[leftPtr]);
      leftPtr--;
    } else if(rightPtr <= nums.size() - 1) {
      result.push_back(nums[rightPtr]);
      rightPtr++;
    }
  }
  std::move(result.begin(), result.end(), std::back_inserter(movedResult));
  return movedResult;
}

void KClosestNumbers() {
  vector<int> result = KClosestNumbers(vector<int>{5, 6, 7, 8, 9}, 3, 7);
  cout << "'K' closest numbers to 'X' are: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;

  result = KClosestNumbers(vector<int>{2, 4, 5, 6, 9}, 3, 6);
  cout << "'K' closest numbers to 'X' are: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;

  result = KClosestNumbers(vector<int>{2, 4, 5, 6, 9}, 3, 10);
  cout << "'K' closest numbers to 'X' are: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;
}

int MaximumDistinctElements(const vector<int>& nums, int k) {
  //prepare frequency map;
  //prepare a min heap based on frequency;
  //greedy algorithm: remove element with least frequency; remove all of the occurence except 1;
  unordered_map<int, int> frequencies;
  for(int num: nums) {
    frequencies[num]++;
  }
  int num_distinct = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>, FrequencyCompare> minHeap;
  for(auto& entry: frequencies) {
    if(entry.second == 1) {
      num_distinct++;
    } else {
      minHeap.push(entry);
    }
  }

  while(k > 0 && minHeap.empty() == false) {
    auto entry = minHeap.top();
    minHeap.pop();
    while(k > 0 && entry.second > 1) {
      k--;
      entry.second--;
    }
    if(entry.second == 1) {
      num_distinct++;
    }
  }

  while(k > 0 && num_distinct > 0) {
    k--;
    num_distinct--;
  }
  return num_distinct;
}


void MaximumDistinctElements() {
  int result =
      MaximumDistinctElements(vector<int>{7, 3, 5, 8, 5, 3, 3}, 2);
  cout << "Maximum distinct numbers after removing K numbers: " << result << endl;

  result = MaximumDistinctElements(vector<int>{3, 5, 12, 11, 12}, 3);
  cout << "Maximum distinct numbers after removing K numbers: " << result << endl;

  result = MaximumDistinctElements(
      vector<int>{1, 2, 3, 3, 3, 3, 4, 4, 5, 5, 5}, 2);
  cout << "Maximum distinct numbers after removing K numbers: " << result << endl;
}


int SumOfElementsK1ToK2(const vector<int>& nums, int k1, int k2) {
  priority_queue<int, vector<int>, greater<>> minHeap;
  for(const auto& num: nums) {
    minHeap.push(num);
  }
  int sumOfElements = 0;
  for(int i = 1; i <= k1; i++) {
    minHeap.pop();
  }
  for(int i = k1+1;i < k2; i++) {
    sumOfElements += minHeap.top();
    minHeap.pop();
  }
  return sumOfElements;
}

void SumOfElementsK1ToK2() {
  int result = SumOfElementsK1ToK2(vector<int>{1, 3, 12, 5, 15, 11}, 3, 6);
  cout << "Sum of all numbers between k1 and k2 smallest numbers: " << result << endl;

  result = SumOfElementsK1ToK2(vector<int>{3, 5, 8, 7}, 1, 4);
  cout << "Sum of all numbers between k1 and k2 smallest numbers: " << result << endl;
}

string ReArrangeString(const string& str) {
  unordered_map<char, int> frequencies;
  for(char ch: str) {
    frequencies[ch]++;
  }
  priority_queue<pair<char, int>, vector<pair<char,int>>, CharFrequencyCompare> maxHeap;
  for(auto& entry: frequencies) {
    maxHeap.push(entry);
  }
  string output = "";
  pair<char, int> previous(-1, -1);
  while(!maxHeap.empty()) {
    auto entry = maxHeap.top();
    maxHeap.pop();
    output += entry.first;
    entry.second--;
    if(previous.second > 0) { //-1/0 not acceptable
      maxHeap.push(previous);
    }
    previous = entry;
  }
  return output.size() == str.size() ? output : "";
}

void ReArrangeString() {
  cout << "Rearranged string: " << ReArrangeString("aappp") << endl;
  cout << "Rearranged string: " << ReArrangeString("Programming") << endl;
  cout << "Rearranged string: " << ReArrangeString("aapa") << endl;
}


string ReArrangeStringKDistanceApart(const string& str, int k) {
  unordered_map<char, int> frequencies;
  for(char ch: str) {
    frequencies[ch]++;
  }
  priority_queue<pair<char, int>, vector<pair<char, int>>, CharFrequencyCompare> maxHeap;
  for(auto entry: frequencies) {
    maxHeap.push(entry);
  }

  string result = "";

  //key point; 0 frequency will contribute to the calculation
  queue<pair<char, int>> queue;

  while(!maxHeap.empty()) {
    auto entry = maxHeap.top();
    maxHeap.pop();
    result += entry.first;
    entry.second--;
    queue.push(entry);
    if(queue.size() == k) {
      auto entry = queue.front();
      queue.pop();
      if(entry.second > 0) {
        maxHeap.push(entry);
      }
    }
  }
  return result.size() == str.size() ? result : "";
}

void ReArrangeStringKDistanceApart() {
  cout << "Reorganized string: " << ReArrangeStringKDistanceApart("Programming", 3) << endl;
  cout << "Reorganized string: "
       << ReArrangeStringKDistanceApart("mmpp", 2) << endl;
  cout << "Reorganized string: "
       << ReArrangeStringKDistanceApart("aab", 2) << endl;
  cout << "Reorganized string: " << ReArrangeStringKDistanceApart("aappa", 3)
       << endl;
}

int ScheduleTasks(vector<char>& tasks, int k) {
  int intervalCount = 0;
  unordered_map<char, int> frequencies;
  for(auto& task: tasks) {
    frequencies[task]++;
  }

  priority_queue<pair<char, int>, vector<pair<char, int>>, CharFrequencyCompare> maxHeap;

  for(auto& entry: frequencies) {
    maxHeap.push(entry);
  }
  while(!maxHeap.empty()) {
    queue<pair<char, int>> waitList;
    int n = k + 1;
    for(; n > 0 && maxHeap.empty() == false; n--) {
      intervalCount++;
      auto entry = maxHeap.top();
      maxHeap.pop();
      if(entry.second > 1) {
        entry.second--;
        waitList.push(entry);
      }
    }
    while(!waitList.empty()) {
      maxHeap.push(waitList.front());
      waitList.pop();
    }
    if(maxHeap.empty() == false) {
      intervalCount += n;
    }
  }
  return intervalCount;
}

void ScheduleTasks() {
  vector<char> tasks = {'a', 'a', 'a', 'b', 'c', 'c'};
  cout << "Minimum intervals needed to execute all tasks: "
       << ScheduleTasks(tasks, 2) << endl;

  tasks = vector<char>{'a', 'b', 'a'};
  cout << "Minimum intervals needed to execute all tasks: "
       << ScheduleTasks(tasks, 3) << endl;
}


class Element {
public:
  int sequenceNumber;
  int num;
  int frequency;

  Element(int seq, int num, int freq) {
    this->sequenceNumber = seq;
    this->num = num;
    this->frequency = freq;
  }
};

struct CustomComparator {
  bool operator()(const Element& e1, const Element& e2) {
    if(e1.frequency == e2.frequency) {
      return e1.sequenceNumber < e2.sequenceNumber;
    } else {
      return e1.frequency < e2.frequency;
    }
  }
};

class FrequencyStack {
private:
  int sequenceNumber = 0;
  unordered_map<int, int> frequencies;
  priority_queue<Element, vector<Element>, CustomComparator> maxHeap;
public:
  virtual void push(int num) {
    frequencies[num]++;
    maxHeap.push({sequenceNumber++, num, frequencies[num]});
  }
  virtual int pop() {
    int num = maxHeap.top().num;
    maxHeap.pop();
    if(frequencies[num] > 1) {
      frequencies[num]--;
    } else {
      frequencies.erase(num);
    }
    return num;
  }
};

void FreqStack() {
  FrequencyStack frequencyStack;
  frequencyStack.push(1);
  frequencyStack.push(2);
  frequencyStack.push(3);
  frequencyStack.push(2);
  frequencyStack.push(1);
  frequencyStack.push(2);
  frequencyStack.push(5);
  cout << frequencyStack.pop() << endl;
  cout << frequencyStack.pop() << endl;
  cout << frequencyStack.pop() << endl;
}

struct ListNode {
  int data;
  ListNode* next;
  ListNode(int d) {
    this->data = d;
    this->next = 0;
  }
};

struct ListCompare {
  bool operator()(const ListNode* x, ListNode* y) {
    return x->data > y->data;
  };
};

ListNode* MergeKSortedLists(const vector<ListNode*>& lists) {
  priority_queue<ListNode*, vector<ListNode*>, ListCompare> minHeap;
  for(auto head: lists) {
    if(head != 0) {
      minHeap.push(head);
    }
  }
  ListNode* newHead = 0;
  ListNode* tail = 0;

  while(!minHeap.empty()) {
    auto entry = minHeap.top();
    minHeap.pop();
    if(!newHead) {
      newHead = tail = entry;
    } else {
      tail->next = entry;
      tail = entry;
    }
    //push the next entry to the heap
    if(entry->next) {
      minHeap.push(entry->next);
    }
  }
  return newHead;
}


void MergeKSortedLists() {
  ListNode *l1 = new ListNode(2);
  l1->next = new ListNode(6);
  l1->next->next = new ListNode(8);

  ListNode *l2 = new ListNode(3);
  l2->next = new ListNode(6);
  l2->next->next = new ListNode(7);

  ListNode *l3 = new ListNode(1);
  l3->next = new ListNode(3);
  l3->next->next = new ListNode(4);

  ListNode *result = MergeKSortedLists(vector<ListNode *>{l1, l2, l3});
  cout << "Here are the elements form the merged list: ";
  while (result != nullptr) {
    cout << result->data << " ";
    result = result->next;
  }
  cout << endl;
}

struct KValCompare {
  bool operator()(const pair<int, pair<int, int>>& x, const pair<int, pair<int, int>>& y) {
    return x.first > y.first;
  }
};

vector<int> MergeKSortedArrays(const vector<vector<int>>& lists) {
  vector<int> result;
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, KValCompare> minHeap;
  for(int i = 0; i < lists.size(); i++) {
    if(lists[i].empty() == false) {
      minHeap.push(make_pair(lists[i][0], make_pair(i, 0)));
    }
  }

  while(minHeap.empty()==false) {
    auto entry = minHeap.top();
    minHeap.pop();
    result.push_back(entry.first);
    entry.second.second++;
    if(lists[entry.second.first].size() > entry.second.second) {
      entry.first = lists[entry.second.first][entry.second.second];
      minHeap.push(entry);
    }
  }
  return result;
}

void MergeKSortedArrays() {
  vector<vector<int>> nums = {{2,6,8}, {3,6,7}, {1,3,4}};
  vector<int> result = MergeKSortedArrays(nums);
  cout << "K Merged arrays: " << endl;
  for(int num: result) {
    cout << num << " ";
  }
  cout << endl;
}

/*
Let there be N element in M sorted arrays;
Kth Smallest Element
Time: O(KLogM)
Space:O(M)
*/

int KthSmallestInMSortedArrays(const vector<vector<int>>& lists, int k) {
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, KValCompare> minHeap;
    for(int i = 0; i < lists.size(); i++) {
      if(lists[i].empty() == false) {
        minHeap.push(make_pair(lists[i][0], make_pair(i, 0)));
      }
    }

    int count  = 0, result = 0;

    while(!minHeap.empty()) {
      auto entry = minHeap.top();
      minHeap.pop();
      result = entry.first;
      count++;
      if(k == count) {
        break;
      }
      entry.second.second++;
      if(lists[entry.second.first].size() > entry.second.second) {
        entry.first = lists[entry.second.first][entry.second.second];
        minHeap.push(entry);
      }
    }
    return result;
}

void KthSmallestInMSortedArrays() {
  vector<vector<int>> lists = {{2, 6, 8}, {3, 6, 7}, {1, 3, 4}};
  int result = KthSmallestInMSortedArrays(lists, 5);
  cout << "Kth smallest number is: " << result;
}

pair<int, int> SmallestRange(const vector<vector<int>>& lists) {
  int rangeStart = 0;
  int rangeEnd = INT32_MAX;
  int currentMax = INT32_MIN;
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, KValCompare> minHeap;
  //note currentMax is analysed only when you are inserting elements into heap
  for(int i = 0; i < lists.size(); i++) {
    if(lists[i].empty() == false) {
      minHeap.push(make_pair(lists[i][0], make_pair(i, 0)));
      currentMax = max(lists[i][0], currentMax);
    }
  }

  while(minHeap.size() == lists.size()) {
    auto entry = minHeap.top();
    minHeap.pop();
    if((rangeEnd - rangeStart) > (currentMax - entry.first)) {
      rangeStart = entry.first;
      rangeEnd = currentMax;
    }
    entry.second.second++;
    if(lists[entry.second.first].size() > entry.second.second) {
      entry.first = lists[entry.second.first][entry.second.second];
      currentMax = max(currentMax, lists[entry.second.first][entry.second.second]);
      minHeap.push(entry);
    }
  }
  return make_pair(rangeStart, rangeEnd);
}

void SmallestRange() {
  vector<vector<int>> lists = {{1, 5, 8}, {4, 12}, {7, 8, 10}};
  auto result = SmallestRange(lists);
  cout << "\nSmallest range is: [" << result.first << ", " << result.second << "]";
}

struct PairCompare {
  bool operator()(const pair<int, int>& x, const pair<int, int>& y) {
    return x.first + x.second > y.first + y.second;
  }
};

vector<pair<int, int>> KLargestSumPairs(const vector<int>& nums1, const vector<int>& nums2, int k) {
  priority_queue<pair<int, int>, vector<pair<int, int>>, PairCompare> minHeap;
  vector<pair<int, int>> result;
  for(int i = 0; i < nums1.size() && i < k; i++) {
    for(int j = 0; j < nums2.size() && j < k; j++) {
      if(minHeap.empty() || minHeap.size() < k) {
        minHeap.push(make_pair(nums1[i], nums2[j]));
      } else if((nums1[i]+nums2[j]) > (minHeap.top().first + minHeap.top().second)) {
        minHeap.pop();
        minHeap.push(make_pair(nums1[i], nums2[j]));
      } else if((nums1[i]+nums2[j]) < (minHeap.top().first + minHeap.top().second)) {
        break;
      }
    }
  }
  while(!minHeap.empty()) {
    result.push_back(minHeap.top());
    minHeap.pop();
  }
  return result;
}

void KLargestSumPairs() {
  auto result = KLargestSumPairs({9, 8, 2}, {6, 3, 1}, 3);
  cout << "\nPairs with largest sum are: ";
  for (pair<int,int> pr : result) {
    cout << "[" << pr.first << ", " << pr.second << "] ";
  }
}

int main() {
  //educative - Two Heaps
  StreamMedian();
  MaximizeCapital();
  Slm();
  FindNextInterval();
  //educative - top K
  FindKLargest();
  FindKthSmallest();
  ClosestDistanceFromOrigin();
  ConnectRopes();
  TopKFrequentNums();
  FrequencySort();
  KthLargestNumberStream();
  KClosestNumbers();
  MaximumDistinctElements();
  SumOfElementsK1ToK2();
  ReArrangeString();
  ReArrangeStringKDistanceApart();
  ScheduleTasks();
  FreqStack();
  //educative - K-Way Merge
  MergeKSortedLists();
  MergeKSortedArrays();
  KthSmallestInMSortedArrays();
  SmallestRange();
  KLargestSumPairs();
  //algo expert

  //structy

  //leetcode

  //amazon
  return 0;
}