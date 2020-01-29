class segment
{
public:
    int tree[400015];

    void SegmentTree(vector<int> &given, int node, int low, int high)
    {
        if (low == high)
        {
            tree[node] = given[low];
            return;
        }
        int left = 2 * node;
        int right = 2 * node + 1;
        int mid = (low + high) / 2;
        SegmentTree(given, left, low, mid);
        SegmentTree(given, right, mid + 1, high);
        tree[node] = tree[left] + tree[right];
    }
    void update(int node, int low, int hi, int i, int value)
    {

        if (low == hi)
        {
            tree[node] = value;
            return;
        }
        int mid = (low + hi) / 2;
        int left = 2 * node;
        int right = left + 1;
        if (i <= mid)
            update(left, low, mid, i, value);
        else
            update(right, mid + 1, hi, i, value);
        tree[node] = tree[left] + tree[right];
    }
    int query(int node, int low, int hi, int i, int j)
    {
        if (i>hi || j<low)
            return 0;
        if (low >= i&&hi <= j)
            return tree[node];
        int mid = (low + hi) / 2;
        int left = 2 * node;
        int right = left + 1;
        int x = query(left, low, mid, i, j);
        int y = query(right, mid + 1, hi, i, j);
        return x + y;
    }
};
