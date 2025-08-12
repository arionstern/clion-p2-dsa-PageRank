/*
#include <catch2/catch_test_macros.hpp>
#include <iostream>

// change if you choose to use a different header name
#include <sstream>
#include <string>
#include "AdjacencyList.h"

using namespace std;

// the syntax for defining a test is below. It is important for the name to be
// unique, but you can group multiple tests with [tags]. A test can have
// [multiple][tags] using that syntax.
TEST_CASE("Example Test Name - Change me!", "[tag]") {
  // instantiate any class members that you need to test here
  int one = 1;

  // anything that evaluates to false in a REQUIRE block will result in a
  // failing test
  REQUIRE(one == 1); // fix me!

  // all REQUIRE blocks must evaluate to true for the whole test to pass
  REQUIRE(true); // also fix me!
}

TEST_CASE("Test 2", "[tag]") {
  // you can also use "sections" to share setup code between tests, for example:
  int one = 1;

  SECTION("num is 2") {
    int num = one + 1;
    REQUIRE(num == 2);
  };

  SECTION("num is 3") {
    int num = one + 2;
    REQUIRE(num == 3);
  };

  // each section runs the setup code independently to ensure that they don't
  // affect each other
}

// You must write 5 unique, meaningful tests for credit on the testing section
// of this project!

// See the following for an example of how to easily test your output.
// This uses C++ "raw strings" and assumes your PageRank outputs a string with
//   the same thing you print.
TEST_CASE("Example PageRank Output Test", "[flag]") {
    string input = R"(7 2
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
gmail.com maps.com)";

    string expectedOutput = R"(facebook.com 0.20
gmail.com 0.20
google.com 0.10
maps.com 0.30
ufl.edu 0.20
)";

    // Set up simulated input
    istringstream in(input);
    int n, p;
    in >> n >> p;
    in.ignore();

    AdjacencyList g;
    for (int i = 0; i < n; i++) {
        string from, to;
        in >> from >> to;
        g.addEdge(from, to);
    }

    string actualOutput = g.PageRank(p);

    REQUIRE(actualOutput == expectedOutput);
}




using namespace std;

// Name: Arion Stern
// UFID: 38256771

//used Chat GPT to come up with ideas for some tests

TEST_CASE("Test 1 - Triangle Cycle", "[pagerank][cycle]") {
    AdjacencyList g;
    g.addEdge("a.com", "b.com");
    g.addEdge("b.com", "c.com");
    g.addEdge("c.com", "a.com");

    string output = g.PageRank(2);
    string expected = "a.com 0.33\nb.com 0.33\nc.com 0.33\n";
    REQUIRE(output == expected);
}

TEST_CASE("Test 2 - Hub Node", "[pagerank][hub]") {
    AdjacencyList g;
    g.addEdge("hub.com", "a.com");
    g.addEdge("hub.com", "b.com");
    g.addEdge("hub.com", "c.com");

    string output = g.PageRank(2);
    string expected = "a.com 0.08\nb.com 0.08\nc.com 0.08\nhub.com 0.00\n";
    REQUIRE(output == expected);
}

TEST_CASE("Test 3 - Dead-End Node", "[pagerank][deadend]") {
    AdjacencyList g;
    g.addEdge("start.com", "end.com");

    string output = g.PageRank(2);
    string expected = "end.com 0.50\nstart.com 0.00\n";
    REQUIRE(output == expected);
}

TEST_CASE("Test 4 - Disconnected Components", "[pagerank][disconnected]") {
    AdjacencyList g;
    g.addEdge("x.com", "y.com");
    g.addEdge("z.com", "w.com");

    string output = g.PageRank(2);
    string expected = "w.com 0.25\nx.com 0.00\ny.com 0.25\nz.com 0.00\n";
    REQUIRE(output == expected);
}

TEST_CASE("Test 5 - Self-Linking Node", "[pagerank][selfloop]") {
    AdjacencyList g;
    g.addEdge("loop.com", "loop.com");

    string output = g.PageRank(2);
    string expected = "loop.com 1.00\n";
    REQUIRE(output == expected);
}



TEST_CASE("Test 7 - Circular Chain With Tail", "[pagerank][tail]") {
    AdjacencyList g;
    g.addEdge("a.com", "b.com");
    g.addEdge("b.com", "c.com");
    g.addEdge("c.com", "a.com");
    g.addEdge("d.com", "a.com"); // tail into the loop

    string output = g.PageRank(2);
    string expected = "a.com 0.50\nb.com 0.25\nc.com 0.25\nd.com 0.00\n";

    REQUIRE(output == expected);
}

TEST_CASE("Test 8 - Self-loop Twice", "[pagerank][selfloop]") {
    AdjacencyList g;
    g.addEdge("a.com", "a.com");
    g.addEdge("a.com", "a.com");

    string output = g.PageRank(2);
    string expected = "a.com 1.00\n";

    REQUIRE(output == expected);
}

TEST_CASE("Test 9 - Self-link and Outlink", "[pagerank][selfplusone]") {
    AdjacencyList g;
    g.addEdge("a.com", "a.com");
    g.addEdge("a.com", "b.com");

    string output = g.PageRank(2);
    string expected = "a.com 0.25\nb.com 0.25\n";

    REQUIRE(output == expected);
}

TEST_CASE("Test - Linear Chain", "[pagerank][chain]") {
    AdjacencyList g;
    g.addEdge("a.com", "b.com");
    g.addEdge("b.com", "c.com");
    g.addEdge("c.com", "d.com");

    string output = g.PageRank(2);
    string expected = "a.com 0.00\nb.com 0.25\nc.com 0.25\nd.com 0.25\n";

    REQUIRE(output == expected);
}


TEST_CASE("Test - Mutual Link Pair", "[pagerank][mutual]") {
    AdjacencyList g;
    g.addEdge("a.com", "b.com");
    g.addEdge("b.com", "a.com");

    string output = g.PageRank(2);
    string expected = "a.com 0.50\nb.com 0.50\n";

    REQUIRE(output == expected);
}

TEST_CASE("Test - Star Topology", "[pagerank][star]") {
    AdjacencyList g;
    g.addEdge("center.com", "a.com");
    g.addEdge("center.com", "b.com");
    g.addEdge("center.com", "c.com");

    string output = g.PageRank(2);
    string expected = "a.com 0.08\nb.com 0.08\nc.com 0.08\ncenter.com 0.00\n";

    REQUIRE(output == expected);
}

TEST_CASE("Test - No In-links", "[pagerank][sink]") {
    AdjacencyList g;
    g.addEdge("a.com", "b.com");
    g.addEdge("b.com", "c.com");

    // d.com is never pointed to
    g.addEdge("c.com", "a.com");

    string output = g.PageRank(2);

    REQUIRE(output.find("d.com 0.00") == string::npos); // need an addEdge to include d.com
}

//random tests from the PageRank Tester

TEST_CASE("Random PageRank Tester Case 1", "[pagerank][random]") {
    string input = R"(10 13
google.com getbootstrap.com
samsung.com ufl.edu
microsoft.com twitter.com
facebook.com ufl.edu
getbootstrap.com mozilla.org
weather.com ufl.edu
stackoverflow.com mozilla.org
google.com ufl.edu
samsung.com google.com
ufl.edu weather.com)";

    string expectedOutput = R"(facebook.com 0.00
getbootstrap.com 0.00
google.com 0.00
microsoft.com 0.00
mozilla.org 0.00
samsung.com 0.00
stackoverflow.com 0.00
twitter.com 0.00
ufl.edu 0.12
weather.com 0.30
)";

    istringstream in(input);
    int n, p;
    in >> n >> p;
    in.ignore();

    AdjacencyList g;
    for (int i = 0; i < n; i++) {
        string from, to;
        in >> from >> to;
        g.addEdge(from, to);
    }

    string actualOutput = g.PageRank(p);
    REQUIRE(actualOutput == expectedOutput);
}


TEST_CASE("Random PageRank Tester Case 2", "[pagerank][random]") {
    string input = R"(10 4
youtube.com aman.com
microsoft.com youtube.com
instagram.com apple.com
roblox.com aman.com
microsoft.com python.org
python.org youtube.com
youtube.com instagram.com
stackoverflow.com python.org
roblox.com instagram.com
instagram.com microsoft.com)";

    string expectedOutput = R"(aman.com 0.11
apple.com 0.05
instagram.com 0.11
microsoft.com 0.05
python.org 0.03
roblox.com 0.00
stackoverflow.com 0.00
youtube.com 0.06
)";

    istringstream in(input);
    int n, p;
    in >> n >> p;
    in.ignore();

    AdjacencyList g;
    for (int i = 0; i < n; i++) {
        string from, to;
        in >> from >> to;
        g.addEdge(from, to);
    }

    string actualOutput = g.PageRank(p);
    REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Random PageRank Tester Case 3 - Single Edge", "[pagerank][random]") {
    string input = R"(1 11
openai.com pcbuildinguf.com)";

    string expectedOutput = R"(openai.com 0.00
pcbuildinguf.com 0.00
)";

    istringstream in(input);
    int n, p;
    in >> n >> p;
    in.ignore();

    AdjacencyList g;
    for (int i = 0; i < n; i++) {
        string from, to;
        in >> from >> to;
        g.addEdge(from, to);
    }

    string actualOutput = g.PageRank(p);
    REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Random PageRank Tester Case 4 - Large Graph", "[pagerank][random]") {
    string input = R"(15 7
github.com python.org
microsoft.com stackoverflow.com
youtube.com samsung.com
github.com twitter.com
getbootstrap.com twitter.com
aman.com apple.com
twitter.com github.com
google.com twitter.com
mozilla.org reactjs.org
github.com chase.com
microsoft.com aman.com
stackoverflow.com youtube.com
stackoverflow.com chase.com
python.org mozilla.org
github.com reactjs.org)";

    string expectedOutput = R"(aman.com 0.00
apple.com 0.00
chase.com 0.00
getbootstrap.com 0.00
github.com 0.01
google.com 0.00
microsoft.com 0.00
mozilla.org 0.01
python.org 0.00
reactjs.org 0.01
samsung.com 0.00
stackoverflow.com 0.00
twitter.com 0.00
youtube.com 0.00
)";

    istringstream in(input);
    int n, p;
    in >> n >> p;
    in.ignore();

    AdjacencyList g;
    for (int i = 0; i < n; i++) {
        string from, to;
        in >> from >> to;
        g.addEdge(from, to);
    }

    string actualOutput = g.PageRank(p);
    REQUIRE(actualOutput == expectedOutput);
}


TEST_CASE("Random PageRank Tester Case 5 - Feedback Loop", "[pagerank][random]") {
    string input = R"(8 4
roblox.com facebook.com
chase.com roblox.com
facebook.com roblox.com
samsung.com roblox.com
roblox.com instagram.com
roblox.com chase.com
facebook.com samsung.com
samsung.com facebook.com)";

    string expectedOutput = R"(chase.com 0.07
facebook.com 0.11
instagram.com 0.07
roblox.com 0.27
samsung.com 0.09
)";

    istringstream in(input);
    int n, p;
    in >> n >> p;
    in.ignore();

    AdjacencyList g;
    for (int i = 0; i < n; i++) {
        string from, to;
        in >> from >> to;
        g.addEdge(from, to);
    }

    string actualOutput = g.PageRank(p);
    REQUIRE(actualOutput == expectedOutput);
}
*/