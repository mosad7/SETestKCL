#ifndef NEGOTIATOR
#define NEGOTIATOR

#include <thread>

#include "Queue.h"
#include "NegotiationData.h"

//Negotiation dataset
struct NgtData;

class Negotiator
{
	//variables
private:
	//buffer to hold input
	Queue<char> m_inputBuffer;
	//separate thread to process input w/o affecting the user interface
	std::thread m_workThread;

	//negotiation data structure
	NegotiationData m_ngtData;
	
	//access controller for the summary generation mechanisim;
	//working thread notifies the requisting UI when summary is ready
	std::mutex m_summaryMutex;
	std::condition_variable m_summaryCondition;
	
	//duration for the simulation process
	std::chrono::milliseconds m_execTime;

	//functions
public:
	Negotiator();
	~Negotiator();

	void Start(bool simulateExecTime = false);
	void Stop();
	void AppendInput(char ch);
	std::string GenerateSummary();
	std::string GenerateHelpText();

	unsigned int GetNumberOfYes();
	unsigned int GetNumberOfNo();

private:
	void WorkFunction();
};

#endif //NEGOTIATOR