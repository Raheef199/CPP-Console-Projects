#pragma warning(disable : 4996)
#include <iostream>
#include "clsDblLinkedList.h";
#include "clsMyQueue.h";
#include "clsMyStack.h";
#include "clsDynamicArray.h";
#include "clsMyQueueArr.h";
#include "clsMyStackArr.h";
#include "clsMyString.h";
#include "clsQueueLine.h";


using namespace std;

int main()
{
    /*clsDblLinkedList<int> MyDblLinkedList;

    if (MyDblLinkedList.IsEmpty()) {
        cout << "\n\nYes List is Empty.\n";
    }
    else {
        cout << "\n\nNo List is not Empty.\n";
    }

    MyDblLinkedList.InsertAtBeginning(5);
    MyDblLinkedList.InsertAtBeginning(4);
    MyDblLinkedList.InsertAtBeginning(3);
    MyDblLinkedList.InsertAtBeginning(2);
    MyDblLinkedList.InsertAtBeginning(1);

    cout << "\nLinked List Content: \n";
    MyDblLinkedList.PrintList();*/

    //cout << "\nNumber of items in the linked list = " << MyDblLinkedList.Size();

    // cout << "\n\nExecuting Clear(). \n";
    // MyDblLinkedList.Clear();
    //cout << "\nNumber of items in the linked list = " << MyDblLinkedList.Size();

    //cout << "\n\nLinked List Content After Reverse: \n";
    //MyDblLinkedList.Reverse();
    //MyDblLinkedList.PrintList();

    //clsDblLinkedList<int>::Node* N;
    //N = MyDblLinkedList.GetNode(4);
    //
    //cout << "\nNode value is: " << N->value;
    //
    //system("pause > 0");

    //cout << "\nItem(2) Value is: " << MyDblLinkedList.GetItem(2);

    //MyDblLinkedList.UpdateItem(2, 500);
    //cout << "\nAfter Updating Item(2): \n";
    //MyDblLinkedList.PrintList();

    //MyDblLinkedList.InsertAfter(1, 500);
    //cout << "\nLinked List Content After Inserting: \n";
    //MyDblLinkedList.PrintList();

    /* ---------------------- Queue Project ------------------------------ */

    //clsMyQueue<int> MyQueue;

    //MyQueue.push(10);
    //MyQueue.push(20);
    //MyQueue.push(30);
    //MyQueue.push(40);
    //MyQueue.push(50);

    //cout << "\nQueue: \n";
    //MyQueue.Print();

    //cout << "\nQueue Size: " << MyQueue.Size();
    //cout << "\nQueue Front: " << MyQueue.front();
    //cout << "\nQueue Back: " << MyQueue.back();

    //MyQueue.pop();
    //cout << "\n\nQueue After pop: \n";
    //MyQueue.Print();

    //// Extension #1
    //cout << "\n\nItem(2) : " << MyQueue.GetItem(2);

    //// Extension #2
    //MyQueue.Reverse();
    //cout << "\n\nQueue after Reverse(): \n";
    //MyQueue.Print();

    //// Extension #3
    //MyQueue.UpdateItem(2, 600);
    //cout << "\n\nQueue after updating Item(2) to 600: \n";
    //MyQueue.Print();

    //// Extension #4
    //MyQueue.InsertAfter(2, 800);
    //cout << "\n\nQueue after Inserting 800 after Item(2): \n";
    //MyQueue.Print();

    //// Extension #5
    //MyQueue.InsertAtFront(1000);
    //cout << "\n\nQueue after Inserting 1000 at front: \n";
    //MyQueue.Print();

    //// Extension #6
    //MyQueue.InsertAtBack(2000);
    //cout << "\n\nQueue after Inserting 1000 at back: \n";
    //MyQueue.Print();

    //// Extension #7
    //MyQueue.Clear();
    //cout << "\n\nQueue after Clear(): \n";
    //MyQueue.Print();

    /*  ---------------- Stack Project ---------------------- */
    
    //clsMyStack<int> MyStack;

    //MyStack.push(10);
    //MyStack.push(20);
    //MyStack.push(30);
    //MyStack.push(40);
    //MyStack.push(50);

    //cout << "\nStack : \n";
    //MyStack.Print();

    //cout << "\nStack Size: " << MyStack.Size();
    //cout << "\nStack Top: " << MyStack.top();
    //cout << "\nStack Bottom: " << MyStack.bottom();

    //MyStack.pop();

    //cout << "\n\nStack After pop(): \n";
    //MyStack.Print();

    //// Extension #1
    //cout << "\nItem (2): " << MyStack.GetItem(2);


    //// Extension #2
    //MyStack.Reverse();
    //cout << "\n\nStack after reverse(): \n";
    //MyStack.Print();

    //// Extension #3
    //MyStack.UpdateItem(2, 600);
    //cout << "\n\nStack After Updating Item(2): \n";
    //MyStack.Print();

    //// Extension #4
    //MyStack.InsertAfter(2, 800);
    //cout << "\n\nStack After Inserting 800 after Item(2): \n";
    //MyStack.Print();

    //// Extension #5
    //MyStack.InsertAtFront(1000);
    //cout << "\n\nStack After Inserting 1000 at front: \n";
    //MyStack.Print();

    //// Extension #6
    //MyStack.InsertAtBack(2000);
    //cout << "\n\nStack After Inserting 2000 at back: \n";
    //MyStack.Print();

    //// Extension #7
    //MyStack.Clear();
    //cout << "\n\nStack After Clear(): \n";
    //MyStack.Print();

    /* ---------------------- Queue Project ------------------------------ */
    
    //clsDynamicArray<int> MyDynamicArray(5);
    //
    //MyDynamicArray.SetItem(0, 10);
    //MyDynamicArray.SetItem(1, 20);
    //MyDynamicArray.SetItem(2, 30);
    //MyDynamicArray.SetItem(3, 40);
    //MyDynamicArray.SetItem(4, 50);
    //
    //cout << "\nIs Empty? " << MyDynamicArray.IsEmpty();
    //cout << "\nArray Size: " << MyDynamicArray.Size() << "\n";
    //cout << "\nArray Items: \n";
    //
    //MyDynamicArray.PrintList();

    //MyDynamicArray.Resize(2);
    //cout << "\nArray Size: " << MyDynamicArray.Size() << "\n";
    //cout << "\nArray Items after resize to 2: \n";
    //MyDynamicArray.PrintList();
    //
    //MyDynamicArray.Resize(10);
    //cout << "\nArray Size: " << MyDynamicArray.Size() << "\n";
    //cout << "\nArray Items after resize to 10: \n";
    //MyDynamicArray.PrintList();

    //cout << "\nItem(2): " << MyDynamicArray.GetItem(2) << "\n";
    //
    //MyDynamicArray.Reverse();
    //cout << "\nArray Items After Reverse(): \n";
    //MyDynamicArray.PrintList();
    //
    //MyDynamicArray.Clear();
    //cout << "\nArray Items after Clear(). \n";
    //MyDynamicArray.PrintList();

    //MyDynamicArray.DeleteItemAt(2);
    //cout << "\nArray Items after Deleting item(2): \n";
    //cout << "\nArray Size: " << MyDynamicArray.Size() << "\n";
    //MyDynamicArray.PrintList();

    //MyDynamicArray.DeleteFirstItem();
    //cout << "\nArray Items after Deleting First Item: \n";
    //cout << "\nArray Size: " << MyDynamicArray.Size() << "\n";
    //MyDynamicArray.PrintList();
    //
    //MyDynamicArray.DeleteLastItem();
    //cout << "\nArray Items after Deleting Last Item: \n";
    //cout << "\nArray Size: " << MyDynamicArray.Size() << "\n";
    //MyDynamicArray.PrintList();

    //int index = MyDynamicArray.Find(30);
    //if (index == -1) {
    //    cout << "\nItem was not Found :-(\n";
    //}
    //else {
    //    cout << "\n30 is found at index : " << index;
    //}
    //
    //MyDynamicArray.DeleteItem(30);
    //cout << "\nArray Items after Deleting 30: \n";
    //cout << "\nArray Size: " << MyDynamicArray.Size() << "\n";
    //MyDynamicArray.PrintList();

    //MyDynamicArray.InsertAt(2, 500);
    //cout << "\n\nArray after inserting 500 at index 2:";
    //cout << "\nArray Size: " << MyDynamicArray.Size() << "\n";
    //cout << "\nArray Items: \n";
    //MyDynamicArray.PrintList();

    //MyDynamicArray.InsertAtBeggining(400);
    //cout << "\n\nArray after inserting 400 at beginning:";
    //cout << "\nArray Size: " << MyDynamicArray.Size() << "\n";
    //MyDynamicArray.PrintList();
    //
    //
    //MyDynamicArray.InsertBefore(2, 500);
    //cout << "\n\nArray after inserting 500 before index 2:";
    //cout << "\nArray Size: " << MyDynamicArray.Size() << "\n";
    //MyDynamicArray.PrintList();
    //
    //MyDynamicArray.InsertAfter(2, 600);
    //cout << "\n\nArray after inserting 600 after index 2:";
    //cout << "\nArray Size: " << MyDynamicArray.Size() << "\n";
    //MyDynamicArray.PrintList();
    //
    //
    //MyDynamicArray.InsertAtEnd(800);
    //cout << "\n\nArray after inserting 800 at End:";
    //cout << "\nArray Size: " << MyDynamicArray.Size() << "\n";
    //MyDynamicArray.PrintList();

    /* --------------------------------- Queue Array Project -------------------------- */
    /*clsMyQueueArr<int> MyQueue;

    MyQueue.push(10);
    MyQueue.push(20);
    MyQueue.push(30);
    MyQueue.push(40);
    MyQueue.push(50);

    cout << "\nQueue: \n";
    MyQueue.Print();

    cout << "\nQueue Size: " << MyQueue.Size();
    cout << "\nQueue Front: " << MyQueue.front();
    cout << "\nQueue Back: " << MyQueue.back();

    MyQueue.pop();

    cout << "\n\nQueue after pop() : \n";
    MyQueue.Print();

    cout << "\n\n Item(2) : " << MyQueue.GetItem(2);

    MyQueue.Reverse();
    cout << "\n\nQueue after reverse() : \n";
    MyQueue.Print();

    MyQueue.UpdateItem(2, 600);
    cout << "\n\nQueue after updating Item(2) to 600 : \n";
    MyQueue.Print();

    MyQueue.InsertAfter(2, 800);
    cout << "\n\nQueue after Inserting 800 after Item(2) : \n";
    MyQueue.Print();

    MyQueue.InsertAtFront(1000);
    cout << "\n\nQueue after Inserting 1000 at front: \n";
    MyQueue.Print();

    MyQueue.InsertAtBack(2000);
    cout << "\n\nQueue after Inserting 2000 at back: \n";
    MyQueue.Print();

    MyQueue.Clear();
    cout << "\n\nQueue after Clear(): \n";
    MyQueue.Print();*/


    /* --------------------------------- Stack Array Project -------------------------- */

    /*clsMyStackArr<int> MyStack;

    MyStack.push(10);
    MyStack.push(20);
    MyStack.push(30);
    MyStack.push(40);
    MyStack.push(50);

    cout << "\nStack: \n";
    MyStack.Print();

    cout << "\nStack Size: " << MyStack.Size();
    cout << "\nStack Front: " << MyStack.Top();
    cout << "\nStack Back: " << MyStack.Bottom();

    MyStack.pop();

    cout << "\n\nStack after pop() : \n";
    MyStack.Print();

    cout << "\n\nStack Item(2) : " << MyStack.GetItem(2);

    MyStack.Reverse();
    cout << "\n\nStack after reverse() : \n";
    MyStack.Print();

    MyStack.UpdateItem(2, 600);
    cout << "\n\nStack after updating Item(2) to 600 : \n";
    MyStack.Print();

    MyStack.InsertAfter(2, 800);
    cout << "\n\nStack after Inserting 800 after Item(2) : \n";
    MyStack.Print();

    MyStack.InsertAtFront(1000);
    cout << "\n\nStack after Inserting 1000 at front: \n";
    MyStack.Print();

    MyStack.InsertAtBack(2000);
    cout << "\n\nStack after Inserting 2000 at back: \n";
    MyStack.Print();

    MyStack.Clear();
    cout << "\n\nStack after Clear(): \n";
    MyStack.Print();*/

    /* --------------------------------- Undo/Redo Project -------------------------- */

    /*cout << "\n\n\t\t\t\t\t\t Undo/Redo Project\n\n";

    clsMyString S1;

    cout << "\nS1 = " << S1.Value << "\n";

    S1.Value = "Mohammed";

    cout << "\nS1 = " << S1.Value << "\n";
    
    S1.Value = "Mohammed2";

    cout << "\nS1 = " << S1.Value << "\n";

    S1.Value = "Mohammed3";

    cout << "\nS1 = " << S1.Value << "\n";

    cout << "\n\nUndo:";
    cout << "\n_________________\n";

    S1.Undo();
    cout << "\nS1 after undo = " << S1.Value << "\n";

    S1.Undo();
    cout << "\nS1 after undo = " << S1.Value << "\n";

    S1.Undo();
    cout << "\nS1 after undo = " << S1.Value << "\n";

    cout << "\n\nRedo: ";
    cout << "\n_________________\n";

    S1.Redo();
    cout << "\nS1 after Redo = " << S1.Value << "\n";

    S1.Redo();
    cout << "\nS1 after Redo = " << S1.Value << "\n";

    S1.Redo();
    cout << "\nS1 after Redo = " << S1.Value << "\n";*/

   
    /*  ---------------------------- Queue Line Project --------------------------------- */

    clsQueueLine PayBillsQueue("A0", 10);
    clsQueueLine SubscriptionsQueue("B0", 5);

    PayBillsQueue.IssueTicket();
    PayBillsQueue.IssueTicket();
    PayBillsQueue.IssueTicket();
    PayBillsQueue.IssueTicket();
    PayBillsQueue.IssueTicket();

    cout << "\nPay Bills Queue Info: \n";
    PayBillsQueue.PrintInfo();

    PayBillsQueue.PrintTicketsLineRTL();
    PayBillsQueue.PrintTicketsLineLTR();

    PayBillsQueue.PrintAllTickets();

    PayBillsQueue.ServeNextClient();
    cout << "\nPay Bills Queue after Serving a client is: \n";
    PayBillsQueue.PrintInfo();

    cout << "\nSubscriptions Queue Info: \n";

    SubscriptionsQueue.IssueTicket();
    SubscriptionsQueue.IssueTicket();
    SubscriptionsQueue.IssueTicket();

    SubscriptionsQueue.PrintInfo();

    SubscriptionsQueue.PrintTicketsLineRTL();
    SubscriptionsQueue.PrintTicketsLineLTR();

    SubscriptionsQueue.PrintAllTickets();

    SubscriptionsQueue.ServeNextClient();
    cout << "\nSubscriptions Queue after Serving a client is: \n";
    SubscriptionsQueue.PrintInfo();

    SubscriptionsQueue.ServeNextClient();
    cout << "\nSubscriptions Queue after Serving a client is: \n";
    SubscriptionsQueue.PrintInfo();

    SubscriptionsQueue.ServeNextClient();
    cout << "\nSubscriptions Queue after Serving a client is: \n";
    SubscriptionsQueue.PrintInfo();

    SubscriptionsQueue.ServeNextClient();
    cout << "\nSubscriptions Queue after Serving a client is: \n";
    SubscriptionsQueue.PrintInfo();


}
