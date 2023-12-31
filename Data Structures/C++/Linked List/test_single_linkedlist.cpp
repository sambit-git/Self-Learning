#include <gtest/gtest.h>
#include<vector>
#include "single_linkedlist.h"

using std::vector;

// Single Node Linked List Test Fixture
class SingleNodeLinkedListTestFixture : public ::testing::Test {
    protected:
        LinkedList<int> ll = LinkedList<int>(10);

        void verifySize(int size){
            EXPECT_EQ(ll.getSize(), size);
        }

        void verifySequence(vector<int> values)
        {
            Node<int> *tmp = ll.getHead();
            for(int value: values){
                EXPECT_EQ(tmp->getData(), value);
                tmp = tmp->getNext();
            }
            EXPECT_EQ(tmp, nullptr);
        }
};

// Test case using Google Test

// Test Single Node Linked List
TEST_F(SingleNodeLinkedListTestFixture, Creation) {
    
    verifySize(1);
    verifySequence({10});
    
    // Verify Head = Tail
    EXPECT_EQ(ll.getHead(), ll.getTail());
    
    // Verify No 2nd Node
    EXPECT_EQ(ll.getHead()->getNext(), nullptr);
}

TEST_F(SingleNodeLinkedListTestFixture, Prepend) {
    // Initialization
    ll.prepend(20);

    // Verify Size & Node Sequence
    verifySize(2);
    verifySequence({20, 10});
}

TEST_F(SingleNodeLinkedListTestFixture, Append) {
    // Initialization
    ll.append(20);
    ll.append(30);

    // Verify Size & Node Sequence
    verifySize(3);
    verifySequence({10, 20, 30});
}


TEST_F(SingleNodeLinkedListTestFixture, InsertBegining) {

    // Initialization
    ll.insert(0, 0);
    ll.append(20);
    ll.prepend(-10);
    ll.insert(-20, 0);

    // LL: -20 -> -10 -> 0 -> 10 -> 20
    // Verify Size & Node Sequence
    verifySize(5);
    verifySequence({-20, -10, 0, 10, 20});

}

TEST_F(SingleNodeLinkedListTestFixture, InsertEnd) {
    // Initialization
    ll.append(20);
    ll.prepend(0);
    // LL: 0 -> 10 -> 20

    ll.insert(15, ll.getSize() - 1);
    // LL: 0 -> 10 -> 15 -> 20
    // Verify Size & Node Sequence
    verifySize(4);
    verifySequence({0, 10, 15, 20});

    ll.insert(40, ll.getSize());
    // LL: 0 -> 10 -> 15 -> 20 -> 40
    // Verify Size & Node Sequence
    verifySize(5);
    verifySequence({0, 10, 15, 20, 40});
}

TEST_F(SingleNodeLinkedListTestFixture, InsertBeyondRange) {
    // Initialization
    ll.append(20);
    ll.prepend(0);
    // LL: 0 -> 10 -> 20

    ll.insert(- 1, 10);
    // Verify Size & Node Sequence
    verifySize(3);
    verifySequence({0, 10, 20});

    ll.append(30);
    ll.insert(40, ll.getSize()+1);
    // LL: 0 -> 10 -> 20 -> 30
    // Verify Size & Node Sequence
    verifySize(4);
    verifySequence({0, 10, 20, 30});
}

TEST_F(SingleNodeLinkedListTestFixture, InsertInBetween) {

    // Initialization
    ll.getHead()->setData(100);
    ll.prepend(10);
    ll.append(1000);
    // LL: 10 -> 100 -> 1000

    ll.insert(20, 1);
    // LL: 10 -> 20 -> 100 -> 1000
    // Verify Size & Node Sequence
    verifySize(4);
    verifySequence({10, 20, 100, 1000});

    ll.insert(40, 2);
    // LL: 10 -> 20 -> 40 -> 100 -> 1000
    // Verify Size & Node Sequence
    verifySize(5);
    verifySequence({10, 20, 40, 100, 1000});

    ll.insert(800, 4);
    // LL: 10 -> 20 -> 40 -> 100 -> 800 -> 1000
    // Verify Size & Node Sequence
    verifySize(6);
    verifySequence({10, 20, 40, 100, 800, 1000});


    ll.insert(400, 4);
    // LL: 10 -> 20 -> 40 -> 100 -> 400 -> 800 -> 1000
    // Verify Size & Node Sequence
    verifySize(7);
    verifySequence({10, 20, 40, 100, 400, 800, 1000});

}

TEST_F(SingleNodeLinkedListTestFixture, Reverse)
{
    // Initialization
    ll.append(9);
    ll.append(8);
    ll.append(7);
    ll.append(6);
    ll.append(5);
    ll.append(4);
    ll.append(3);
    ll.append(2);
    ll.append(1);
    ll.append(0);

    verifySequence({10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
    verifySize(11);
    EXPECT_EQ(ll.getHead()->getData(), 10);
    EXPECT_EQ(ll.getTail()->getData(), 0);
    ll.reverse();
    verifySequence({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    verifySize(11);
    EXPECT_EQ(ll.getHead()->getData(), 0);
    EXPECT_EQ(ll.getTail()->getData(), 10);
}

TEST_F(SingleNodeLinkedListTestFixture, Sort)
{
    // Initialization
    ll.append(9);
    ll.append(7);
    ll.append(6);
    ll.append(8);
    ll.append(5);
    ll.append(0);
    ll.append(1);
    ll.append(3);
    ll.append(2);
    ll.append(4);

    verifySequence({10, 9, 7, 6, 8, 5, 0, 1, 3, 2, 4});
    verifySize(11);
    EXPECT_EQ(ll.getHead()->getData(), 10);
    EXPECT_EQ(ll.getTail()->getData(), 4);
    ll.sort();
    verifySequence({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    verifySize(11);
    EXPECT_EQ(ll.getHead()->getData(), 0);
    EXPECT_EQ(ll.getTail()->getData(), 10);
}

TEST_F(SingleNodeLinkedListTestFixture, PopFirst)
{
    // Initialization
    ll.prepend(0);
    ll.prepend(-10);
    ll.prepend(-20);
    ll.append(20);
    ll.append(30);
    ll.append(40);

    verifySequence({-20, -10, 0, 10, 20, 30, 40});
    verifySize(7);
    EXPECT_EQ(ll.getHead()->getData(), -20);
    EXPECT_EQ(ll.getTail()->getData(), 40);
    int element = ll.popFirst();
    verifySequence({-10, 0, 10, 20, 30, 40});
    verifySize(6);
    EXPECT_EQ(ll.getHead()->getData(), -10);
    EXPECT_EQ(ll.getTail()->getData(), 40);
    EXPECT_EQ(element, -20);
}

TEST_F(SingleNodeLinkedListTestFixture, PopLast)
{
    // Initialization
    ll.prepend(0);
    ll.prepend(-10);
    ll.prepend(-20);
    ll.append(20);
    ll.append(30);
    ll.append(40);

    verifySequence({-20, -10, 0, 10, 20, 30, 40});
    verifySize(7);
    EXPECT_EQ(ll.getHead()->getData(), -20);
    EXPECT_EQ(ll.getTail()->getData(), 40);
    int element = ll.popLast();
    verifySequence({-20, -10, 0, 10, 20, 30});
    verifySize(6);
    EXPECT_EQ(ll.getHead()->getData(), -20);
    EXPECT_EQ(ll.getTail()->getData(), 30);
    EXPECT_EQ(element, 40);
}


// Zero Node Linked List Test Fixture
class ZeroNodeLinkedListTestFixture : public ::testing::Test {
    protected:
        LinkedList<int> ll = LinkedList<int>();

        void verifySize(int size){
            EXPECT_EQ(ll.getSize(), size);
        }

        void verifySequence(vector<int> values)
        {
            Node<int> *tmp = ll.getHead();
            for(int value: values){
                EXPECT_EQ(tmp->getData(), value);
                tmp = tmp->getNext();
            }
            EXPECT_EQ(tmp, nullptr);
        }
};


// Test Single Node Linked List
TEST_F(ZeroNodeLinkedListTestFixture, Creation) {
    
    verifySize(0);
    
    // Verify Head = Tail
    EXPECT_EQ(ll.getHead(), ll.getTail());
    
    // Verify No 2nd Node
    EXPECT_EQ(ll.getHead(), nullptr);
}

TEST_F(ZeroNodeLinkedListTestFixture, Prepend) {
    // Initialization
    ll.prepend(20);

    // Verify Size & Node Sequence
    verifySize(1);
    verifySequence({20});
}

TEST_F(ZeroNodeLinkedListTestFixture, Append) {
    // Initialization
    ll.append(20);
    ll.append(30);

    // Verify Size & Node Sequence
    verifySize(2);
    verifySequence({20, 30});
}


TEST_F(ZeroNodeLinkedListTestFixture, InsertBegining) {

    // Initialization
    ll.insert(0, 0);
    ll.append(20);
    ll.prepend(-10);
    ll.insert(-20, 0);

    // LL: -20 -> -10 -> 0 -> 20
    // Verify Size & Node Sequence
    verifySize(4);
    verifySequence({-20, -10, 0, 20});

}

TEST_F(ZeroNodeLinkedListTestFixture, InsertEnd) {
    // Initialization
    ll.append(20);
    ll.prepend(0);
    // LL: 0 -> 20

    ll.insert(15, ll.getSize() - 1);
    // LL: 0 -> 15 -> 20
    // Verify Size & Node Sequence
    verifySize(3);
    verifySequence({0, 15, 20});

    ll.insert(40, ll.getSize());
    // LL: 0 -> 15 -> 20 -> 40
    // Verify Size & Node Sequence
    verifySize(4);
    verifySequence({0, 15, 20, 40});
}

TEST_F(ZeroNodeLinkedListTestFixture, InsertBeyondRange) {
    // Initialization
    ll.append(20);
    ll.prepend(0);
    // LL: 0 -> 20

    ll.insert(- 1, 10);
    // Verify Size & Node Sequence
    verifySize(2);
    verifySequence({0, 20});

    ll.append(30);
    ll.insert(40, ll.getSize()+1);
    // LL: 0 -> 20 -> 30
    // Verify Size & Node Sequence
    verifySize(3);
    verifySequence({0, 20, 30});
}

TEST_F(ZeroNodeLinkedListTestFixture, InsertInBetween) {

    // Initialization
    ll.prepend(10);
    ll.append(1000);
    // LL: 10 -> 1000

    ll.insert(20, 1);
    // LL: 10 -> 20 -> 1000
    // Verify Size & Node Sequence
    verifySize(3);
    verifySequence({10, 20, 1000});

    ll.insert(40, 2);
    // LL: 10 -> 20 -> 40 -> 1000
    // Verify Size & Node Sequence
    verifySize(4);
    verifySequence({10, 20, 40, 1000});

    ll.insert(800, 4);
    // LL: 10 -> 20 -> 40 -> 1000 -> 800
    // Verify Size & Node Sequence
    verifySize(5);
    verifySequence({10, 20, 40, 1000, 800});


    ll.insert(400, 4);
    // LL: 10 -> 20 -> 40 -> 1000 -> 400 -> 800
    // Verify Size & Node Sequence
    verifySize(6);
    verifySequence({10, 20, 40, 1000, 400, 800});

}

TEST_F(ZeroNodeLinkedListTestFixture, Reverse)
{
    // Initialization
    ll.append(9);
    ll.append(8);
    ll.append(7);
    ll.append(6);
    ll.append(5);
    ll.append(4);
    ll.append(3);
    ll.append(2);
    ll.append(1);
    ll.append(0);

    verifySequence({9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
    verifySize(10);
    EXPECT_EQ(ll.getHead()->getData(), 9);
    EXPECT_EQ(ll.getTail()->getData(), 0);
    ll.reverse();
    verifySequence({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    verifySize(10);
    EXPECT_EQ(ll.getHead()->getData(), 0);
    EXPECT_EQ(ll.getTail()->getData(), 9);
}

TEST_F(ZeroNodeLinkedListTestFixture, Sort)
{
    // Initialization
    ll.append(9);
    ll.append(7);
    ll.append(6);
    ll.append(8);
    ll.append(5);
    ll.append(0);
    ll.append(1);
    ll.append(3);
    ll.append(2);
    ll.append(4);

    verifySequence({9, 7, 6, 8, 5, 0, 1, 3, 2, 4});
    verifySize(10);
    EXPECT_EQ(ll.getHead()->getData(), 9);
    EXPECT_EQ(ll.getTail()->getData(), 4);
    ll.sort();
    verifySequence({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    verifySize(10);
    EXPECT_EQ(ll.getHead()->getData(), 0);
    EXPECT_EQ(ll.getTail()->getData(), 9);
}

TEST_F(ZeroNodeLinkedListTestFixture, PopFirst)
{
    // Initialization
    ll.prepend(0);
    ll.prepend(-10);
    ll.prepend(-20);
    ll.append(20);
    ll.append(30);
    ll.append(40);

    verifySequence({-20, -10, 0, 20, 30, 40});
    verifySize(6);
    EXPECT_EQ(ll.getHead()->getData(), -20);
    EXPECT_EQ(ll.getTail()->getData(), 40);
    int element = ll.popFirst();
    verifySequence({-10, 0, 20, 30, 40});
    verifySize(5);
    EXPECT_EQ(ll.getHead()->getData(), -10);
    EXPECT_EQ(ll.getTail()->getData(), 40);
    EXPECT_EQ(element, -20);
}

TEST_F(ZeroNodeLinkedListTestFixture, PopLast)
{
    // Initialization
    ll.prepend(0);
    ll.prepend(-10);
    ll.prepend(-20);
    ll.append(20);
    ll.append(30);
    ll.append(40);

    verifySequence({-20, -10, 0, 20, 30, 40});
    verifySize(6);
    EXPECT_EQ(ll.getHead()->getData(), -20);
    EXPECT_EQ(ll.getTail()->getData(), 40);
    int element = ll.popLast();
    verifySequence({-20, -10, 0, 20, 30});
    verifySize(5);
    EXPECT_EQ(ll.getHead()->getData(), -20);
    EXPECT_EQ(ll.getTail()->getData(), 30);
    EXPECT_EQ(element, 40);
}

// Run Tests
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// compile: g++ -o runtest test_single_linkedlist.cpp -lgtest -lgtest_main -pthread
// run: ./runtest