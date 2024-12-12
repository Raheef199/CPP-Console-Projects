#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include "clsQueueLine.h";

using namespace std;

int main()
{
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
