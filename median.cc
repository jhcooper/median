/*
 * Determines the median of a stream of integers in O(nlogn) time
 * Variables:
 * lt - the queue containing values less than the current median (max queue)
 * gt - the queue containing values greater than the current median (min queue)
 * Notes:
 * Integers stored in the gt queue are stored as negative numbers
 */

#include <iostream>
#include <queue>
using namespace std;
/*
 * Returns the comparable median for use in inputting new integers
 * If gt contains more elements than lt, the median then
 * lies on top of the greater than queue, and vice versa.
 * If both queues contain the same number of elements, the comparable
 * median is set equal to the top element of the gt queue
 */
int median (priority_queue<int> &lt, priority_queue<int> &gt){
    int median;
    if(gt.size() > lt.size()){
        median = -gt.top();
    }
    else if(gt.size() < lt.size()){
        median = lt.top();
    }
    else{
        median = lt.top();
    }
    return median;
}
/*
 * Balances two queues so that they differ in size by no more than one
 * If one queue contains more than 1 additional element, the top of the
 * queue with more elements is popped, sign reversed, and pushed to the other
 * queue
 */
void balanceHeap(priority_queue<int> &lt,priority_queue<int> &gt){
    int left = lt.size();
    int right = gt.size();
    int temp;
    if(left > right+1){
        temp = lt.top();
        lt.pop();
        gt.push(temp * -1);//stores as a negative value
    }
    else if(right > left+1){
        temp = gt.top() * -1; //undoes the negative
        gt.pop();
        lt.push(temp);
    }
}
/*
 *Determines whether a newly inputted integer gets put in the min or max stack
 *If both stacks are empty (this is the first integer entered), the element is
 * defaulted to the top of the max queue (lt)
 * If the queues are not empty and the element is less than the median, it is
 * pushed to lt. If it is greater than the median, it is pushed to gt
 * Makes a call to balanceHeap
 */
void insert (int elem, priority_queue<int> &lt,priority_queue<int> &gt) {

    if (lt.empty() && gt.empty()) {
        lt.push(elem);
    } else {
        int med = median(lt, gt);
        if (elem <= med) {
            lt.push(elem);
        } else {
            gt.push(-elem);
        }
        balanceHeap(gt, lt);
    }
}
/*
 * Prints the median from the string of integers pushed so far
 * If the gt queue is empty, push to the lt queue
 * If lt contains more elements, print its .top() value
 * If gt contains more elements, print its .top() value
 * If the queues contain the same number of elements, print the
 * .top() of both queues
 */
void printMed(priority_queue <int> &lt, priority_queue <int> &gt){
    if (gt.empty()){
        cout << lt.top() << endl;
    }
    else{
        int left = lt.size();
        int right = gt.size();
        if (left>right){
            cout << lt.top() << endl;
        }
        else if (right>left){
            cout << -gt.top() << endl;
        }
        else{
            cout << lt.top() << ", " << -gt.top() << endl;
        }
    }
}
/*
 * Main function to print the median of a sequence of integers
 * after each integer input
 * Prompts the user to enter 'P' to push an integer or 'Q' to quit
 * Then prompts a user for an integer to push
 * Makes calls to insert(int,&pq,&pq) and printMed(&pq,&pq)
 */
int main(){
    char action;
    int input;
    priority_queue<int> lt,gt;
    while (1){
        cout << "Enter 'P' to push an integer or 'Q' to quit" << endl;
        cin >> action;
        switch (action){
            case 'P': case 'p':
                cout << "Enter an integer to push:" << endl;
                cin >> input;
                insert(input,lt,gt);
                cout << "Median: ";
                printMed(lt,gt);
                break;
            case 'Q': case 'q':
                return 0;
            default:
                cout << "Please enter 'P' to push or 'Q' to quit" << endl;
                break;
        }
    }
}
