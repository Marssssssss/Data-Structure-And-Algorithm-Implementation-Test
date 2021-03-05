// O(nlogn)


void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    //sort
    int i;
    vector<int> left_part(mid - left + 1, 0), right_part(right - mid);
    for (i = 0; i < mid - left + 1; i++) left_part[i] = arr[left + i];
    for (i = 0; i < right - mid; i++) right_part[i] = arr[mid + i + 1];
    int left_idx = 0, right_idx = 0;
    int t = left;
    while (t != right + 1) {
        if (left_idx == mid - left + 1) {
            arr[t++] = right_part[right_idx++];
        }
        else if (right_idx == right - mid) {
            arr[t++] = left_part[left_idx++];
        }
        else if (left_part[left_idx] <= right_part[right_idx]) {
            arr[t++] = left_part[left_idx++];
        }
        else {
            arr[t++] = right_part[right_idx++];
        }
    }
}
