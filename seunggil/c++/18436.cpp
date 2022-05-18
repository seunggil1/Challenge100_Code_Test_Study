#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class segmentTree {
	const vector<int>& orginalData;
	vector<int> treeData;

public:
	// 홀수인지 짝수인지 나타내는 세그먼트
	bool odd = false;

	segmentTree(const vector<int>& data, bool type): orginalData(data), odd(type) {
		treeData = vector<int>(data.size()*4);
	}


	int init(int start, int end, int node) {
		if (start == end) {
			if (odd) {
				treeData[node] = orginalData[start] % 2 == 1 ? 1 : 0;
			}
			else {
				treeData[node] = orginalData[start] % 2 == 0 ? 1 : 0;
			}
			return treeData[node];
		}
		else {
			int mid = (start + end) / 2;
			return treeData[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
		}
	}

	int getCount(int start, int end, int targetStart, int targetEnd, int node) {
		if (start > targetEnd || end < targetStart)
			return 0;
		else if (targetStart <= start && targetEnd >= end) {
			return treeData[node];
		}
		else {
			int mid = (start + end) / 2;
			return getCount(start, mid, targetStart, targetEnd, node * 2) + getCount(mid + 1, end, targetStart, targetEnd, node * 2 + 1);
		}
	}

	int update(int start, int end, int targetIdx, int node) {
		if (start > targetIdx || end < targetIdx)
			return treeData[node];
		else if (start == end) {
			if (odd) {
				treeData[node] = orginalData[targetIdx] % 2 == 1 ? 1 : 0;
			}
			else {
				treeData[node] = orginalData[targetIdx] % 2 == 0 ? 1 : 0;
			}
			return treeData[node];
		}
		else {
			int mid = (start + end) / 2;
			return treeData[node] = update(start, mid, targetIdx, node * 2) + update(mid + 1, end, targetIdx, node * 2 + 1);
		}
	}

};

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector<int> inputData(n+1);
	
	for (int i = 1; i <= n; i++) {
		cin >> inputData[i];
	}

	segmentTree oddTree(inputData, true);
	segmentTree evenTree(inputData, false);

	oddTree.init(1, n, 1);
	evenTree.init(1, n, 1);

	int query;
	cin >> query;

	for (int j = 0; j < query; j++) {
		int q, a, b;
		cin >> q >> a >> b;

		switch (q)
		{
		case 1:
			inputData[a] = b;
			oddTree.update(1, n, a, 1);
			evenTree.update(1, n, a, 1);
			break;

		case 2:
			cout << evenTree.getCount(1, n, a, b, 1) << '\n';
			break;

		case 3:
			cout << oddTree.getCount(1, n, a, b, 1) << '\n';
			break;

		default:
			assert(false);
			break;
		}
	}

	return 0;
}