#include "../inc/quick_sorter.h"

/// <summary>
/// Sorts an array using the quicksort algorithm according a pivot method. 
/// </summary>
/// <param name="vector"></param>
/// <param name="method"></param>
/// <returns>The number of comparisons between values needed to sort the array.</returns>
int QuickSorter::QuickSort(std::vector<unsigned long>& vector, PivotMethod method) {

	auto vecLength = vector.size();
	if (vecLength <= 1) return 0;

	int numComparisons = 0;
	int pivotIndex = -1;
	switch (method) {
		case PivotMethod::ChooseFirst:
			pivotIndex = 0;
			break;
		case PivotMethod::ChooseLast:
			pivotIndex = vector.size() - 1;
			break;
		case PivotMethod::ChooseMedianOfThree:
			pivotIndex = QuickSorter::ChooseMedianOfThree(vector);
			break;
		default:
			throw "Yo pick a pivot method";
	}

	// Exchange pivot element with first element before partition.
	std::swap(vector[pivotIndex], vector[0]);

	int boundaryIdx = PartitionSubroutine(vector);
	// Pivot element was compared to every other element in array. 
	numComparisons += vector.size() - 1;

	// Split into smaller arrays, where vector initialization does not include final specified value.
	std::vector<unsigned long> smallerValuedSubArray(vector.begin(), vector.begin() + boundaryIdx - 1);
	// Skip pivot itself at boundaryIdx - 1.
	std::vector<unsigned long> LargerValuedSubArray(vector.begin() + boundaryIdx, vector.end());

	// Add recursive comparisons. 
	numComparisons += QuickSort(smallerValuedSubArray, method);
	numComparisons += QuickSort(LargerValuedSubArray, method);
	return numComparisons;
}

/// <summary>
/// Picks the first, last, and median value of an array, and returns the median of those values.
/// </summary>
/// <param name="vector"></param>
/// <returns></returns>
int QuickSorter::ChooseMedianOfThree(const std::vector<unsigned long>& vector) {
	if (vector.size() < 3) return 0;

	int firstIdx = 0;
	auto firstElement = vector.front();
	int middleIdx = (vector.size() - 1) / 2;
	auto middleElement = vector[middleIdx];
	int lastIdx = vector.size() - 1;
	auto lastElement = vector.back();

	// Instead of some fancy, unreadable way to compute median of three, just cover the 6 cases.
	if ((firstElement <= middleElement) && (middleElement <= lastElement)) return middleIdx;
	if ((firstElement <= lastElement) && (lastElement <= middleElement)) return lastIdx;
	if ((middleElement <= firstElement) && (firstElement <= lastElement)) return firstIdx;
	if ((middleElement <= lastElement) && (lastElement <= firstElement)) return lastIdx;
	if ((lastElement <= firstElement) && (firstElement <= middleElement)) return firstIdx;
	return middleIdx;
}

/// <summary>
/// Partitions an array into values that are smaller and larger than a pivot value.
/// Assumes the pivot value has been placed at the start of the array. Note that
/// there is a simpler partition algorithm that uses O(n) more memory to copy
/// values over to a new array.
/// </summary>
/// <param name="vector"></param>
/// <returns></returns>
int QuickSorter::PartitionSubroutine(std::vector<unsigned long>& vector) {
	auto pivotElement = vector.front();
	// Index for leftmost element bigger than pivot, excluding pivot. 
	int boundaryIdx = 1;
	for (auto i = boundaryIdx; i < vector.size(); ++i) {
		if (vector[i] < pivotElement) {
			// swap current element with the leftmost element thats bigger than the pivot. 
			std::swap(vector[i], vector[boundaryIdx]);
			// Left most value bigger than pivot now resides one more element to the right. 
			++boundaryIdx;
		} // Else do nothing, since elements larger than pivot should stay right.
	}
	// Finally move pivot to partition the two subarrays. 
	std::swap(vector[0], vector[boundaryIdx - 1]);

	// Return starting index of right array.
	return boundaryIdx;
}
