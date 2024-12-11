#pragma once
#include <iostream>
#include <queue>
#include <ctime>

using namespace std;

class clsQueueLine {
private:
	class TicketInfo {
	public:
		int TotalTickets;
		int ServedClients;
		int WaitingClients;
	};

	queue <TicketInfo> _MyTicket;
	int _QueueDuration;
	string _Code;

	string _GetDateAndTime() {
		short day, month, year, hour, min, sec;

		time_t t = time(0);
		tm* now = localtime(&t);

		day = now->tm_wday;
		month = now->tm_mon + 1;
		year = now->tm_year + 1900;
		hour = now->tm_hour;
		min = now->tm_min;
		sec = now->tm_sec;

		return to_string(day) + "/" + to_string(month) + "/" + to_string(year) +
			" - " + to_string(hour) + ":" + to_string(min) + ":" + to_string(sec);
	}


public:

	TicketInfo Ticket;
	int EstimatedTime;

	clsQueueLine(string Code, int QueueDuration) {
		_Code = Code;
		_QueueDuration = QueueDuration;
		EstimatedTime = QueueDuration;
	}

	string GetCode() {
		return _Code;
	}

	void SetDuration(int QueueDuration) {
		_QueueDuration = QueueDuration;
	}

	int GetDuration() {
		return _QueueDuration;
	}

	// Specific to Microsoft Visual Studio (Won't work on other IDE'S) 
	__declspec(property(get = GetDuration, put = SetDuration)) int Duration;

	void PrintInfo() {

		cout << "\n\t\t\t\t________________________________\n";
		cout << "\n\t\t\t\t\t    Queue Info ";
		cout << "\n\t\t\t\t________________________________\n";
		if (Ticket.ServedClients > Ticket.TotalTickets) {
			cout << "\n\t\t\t\t    No More Clients To Serve!";
		}
		else {
		    cout << "\n\t\t\t\tPrefix          = " << GetCode();
		    cout << "\n\t\t\t\tTotal Tickets   = " << Ticket.TotalTickets;
		    cout << "\n\t\t\t\tServed Clients  = " << Ticket.ServedClients;
		    cout << "\n\t\t\t\tWaiting Clients = " << Ticket.WaitingClients;
		}
		cout << "\n\t\t\t\t________________________________\n";
	}

	void PrintTicketInfo(int order) {
		cout << "\n\t\t\t\t\t_______________________\n";
		cout << "\n\t\t\t\t\t           " << GetCode() << order << "\n";
		cout << "\n\t\t\t\t\t  " << _GetDateAndTime();
		cout << "\n\t\t\t\t\t  Waiting Clients = " << Ticket.WaitingClients;
		cout << "\n\t\t\t\t\t     Serve Time In\n\t\t\t\t\t      " << Duration << " Minutes.";
		cout << "\n\t\t\t\t\t_______________________\n";

	}

	void IssueTicket() {

		_MyTicket.push(Ticket);
		Ticket.TotalTickets++;
		Ticket.WaitingClients++;

	}

	void PrintTicketsLineRTL() {
		cout << "\n\t\tTickets: ";
		for (int i = 0; i <= _MyTicket.size() - 1; i++) {
			cout << GetCode() << i + 1 << "  <--  ";
		}
	}
	
	void PrintTicketsLineLTR() {
		cout << "\n\n\t\tTickets: ";
		for (int i = _MyTicket.size() - 1; i >= 0; i--) {
			cout << GetCode() << i + 1 << "  -->  ";
		}
	}

	void PrintAllTickets() {
		cout << "\n\n\t\t\t\t\t      --Tickets-- ";
		if (_MyTicket.empty()) {
			cout << "\n\n\t\t\t\t\t      --No Tickets Available!-- ";
		}
		for (int i = 0; i <= _MyTicket.size() - 1; i++) {
			Duration += EstimatedTime;
			Ticket.WaitingClients = i + 1;
			if (i == 0) {
				Duration = 0;
			}
			PrintTicketInfo(i + 1);
		}
	}

	void ServeNextClient() {
		while (!_MyTicket.empty()) {
			_MyTicket.pop();
		}

		Ticket.ServedClients++;
		Ticket.WaitingClients--;

	}
};

