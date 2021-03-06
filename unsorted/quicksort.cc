// quicksort.cc - Quicksort quiz by Sergey 2015

/*
Quicksort in c++

*/

// Standard modules
#include <bits/stdc++.h>

using namespace std;


///////////////////////////////////////////////////////////////////////////////
// Quicksort Class
///////////////////////////////////////////////////////////////////////////////


class Quicksort { public:

    static int const N = 100001;

    int imax;
    int nums[N];

    stack<pair<int, int> > part;

    Quicksort(){

        // Decoding input max sizes
        cin >> imax;
        if (imax > N) {
            cout << "FATAL: Increase N to " << imax << endl; exit(1);
        }

        // Decoding input list
        for(int i = 0; i < imax; i++) cin >> nums[i];
    }

    bool iterate() {
        if (part.empty()) return false;
        partition(part.top().first, part.top().second);
        return true;

    }

    partition(int low, int high) {
        int store = low;
        int pivot = nums[high-1];
        for (int i=low; i < high; i++)
            if (nums[i] <= pivot) swap(nums[i], nums[store++]);

        part.pop();
        if (low != store - 1) part.push(make_pair(low, store - 1));
        if (store != high) part.push(make_pair(store, high));
    }

    string str() {
        ostringstream resstr;
        bool first = true;
        for(int i = 0; i < imax; i++) {
            if (not first) resstr << " ";
            first = false;
            resstr << nums[i];
        }
        return resstr.str();
    }

    string calculate(){

        part.push(make_pair(0, imax));
        while(iterate()){}

        return str();
    }
};


///////////////////////////////////////////////////////////////////////////////
// Quicksort Class test helping functions
///////////////////////////////////////////////////////////////////////////////

Quicksort* class_wrap_input(const string& test="") {

    streambuf* orig = cin.rdbuf();
    istringstream input(test);
    if (test != "") {
        cin.rdbuf(input.rdbuf());
    };
    Quicksort* d = new Quicksort();
    if (test != "") cin.rdbuf(orig);
    return d;
}

string calculate(const string& test="") {
    Quicksort* d = class_wrap_input(test);
    string result = d->calculate();
    delete d;
    return result;
}

///////////////////////////////////////////////////////////////////////////////
// Unit tests base Class
///////////////////////////////////////////////////////////////////////////////


class Unittest { public:

    #define CHECK(a, b)\
        test_fail_err(a, b, #a, #b, __FILE__, __LINE__, __FUNCTION__);
    #define CHECKT(a)\
        test_fail_err(a, 1, #a, "true", __FILE__, __LINE__, __FUNCTION__);
    #define CHECKS(a, b)\
        test_fail_errs(a, b, #a, #b, __FILE__, __LINE__, __FUNCTION__);

    int test_cnt, fail_cnt, fail;
    string status, fail_msg;

    Unittest() {
        test_cnt = fail_cnt = fail = 0;
        status = "OK";
    }

    // Override this function in derived class
    virtual test_list() {
        test_basic();
        test_done();
    }

    test_basic() { CHECKT("Base class basic test" == ""); }

    run() {
        test_list();
        double elp_secs = double(clock()) / CLOCKS_PER_SEC;
        cout << endl;
        if (fail_cnt > 0) cout << fail_msg;
        cout << "--------------------------------------------------" << endl;
        cout << "Ran " << test_cnt << " tests in " << elp_secs << "s" << endl;
        cout << endl;
        if (fail_cnt > 0) cout << "FAILED (failures=" << fail_cnt << ")";
        else cout << status << endl;
        if (fail_cnt > 0) return 1;
    }

    test_fail_hdr(const string& stra, const string& strb,
            const string& file, int line, const string& function) {
        fail_cnt ++;
        fail = 1;
        ostringstream msg;
        msg << "==================================================" << endl;
        msg << "FAIL: " << function << endl;
        msg << "--------------------------------------------------" << endl;
        msg << "File \"" << file << "\", line " << line;
        msg << " in " << function << endl;
        msg << "  Checking " << stra << " == " << strb << endl;
        fail_msg += msg.str();
    }

    test_fail_err(long long a, long long b,
            const string& stra, const string& strb,
            const string& file, int line, const string& function) {
        if (a == b) return 0;
        test_fail_hdr(stra, strb, file, line, function);
        ostringstream msg;
        msg << "  Error: " << a << " ! = " << b << endl << endl;
        fail_msg += msg.str();
    }

    test_fail_errs(const string& a, const string& b,
            const string& stra, const string& strb,
            const string& file, int line, const string& function) {
        if (a == b) return 0;
        test_fail_hdr(stra, strb, file, line, function);
        ostringstream msg;
        msg << "  Error: \"" << a << "\" ! = \"" << b << "\"" << endl;
        msg << endl;
        fail_msg += msg.str();
    }

    test_done() {
        test_cnt ++;
        if (fail == 0) cout << ".";
        else cout << "F";
        fail = 0;
    }
};


///////////////////////////////////////////////////////////////////////////////
// Local Unit tests
///////////////////////////////////////////////////////////////////////////////


class LocalUnittest: public Unittest {

    test_class_basic_functions() {

        // Constructor test
        string test = "8\n8 3 4 2 1 3 3 5";
        Quicksort* d = class_wrap_input(test);
        CHECK(d->imax, 8);
        CHECK(d->nums[0], 8);

        // Misc functions tests
        CHECKT(not d->iterate());

        d->part.push(make_pair(0, 8));
        CHECKT(d->iterate());
        CHECKS(d->str(), "3 4 2 1 3 3 5 8");
        CHECK(d->part.size(), 2);

        // Sample test 1
        string result = d->calculate();
        CHECKS(result, "1 2 3 3 3 4 5 8");
    }

    test_sample_tests() {

    }

    test_time_limit_test() {

        int imax = 1000;
        string test;
        ostringstream o_test;

        o_test << imax << endl;
        for(int i = 0; i < imax; i++) o_test << i << " ";
        test = o_test.str();

        double start = double(clock()) / CLOCKS_PER_SEC;
        Quicksort* d = class_wrap_input(test);

        double calc = double(clock()) / CLOCKS_PER_SEC;
        d->calculate();

        double stop = double(clock()) / CLOCKS_PER_SEC;
        cout << "Time Test: " << stop - start << "s (input " << calc - start;
        cout << "s calc " << stop - calc << "s)" << endl;
    }

    test_list() {
        test_class_basic_functions();
        test_done();
        test_sample_tests();
        test_done();
        test_time_limit_test();
        test_done();
    }
};

///////////////////////////////////////////////////////////////////////////////
// Main Execution
///////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[]) {

    // Faster cin and cout
    ios_base::sync_with_stdio(0);cin.tie(0);

    cout << calculate() << endl;
    return 0;
}

