
#include "Negotiator.h"

#include <iostream>

#include "SETestKCLConfig.h"

Negotiator::Negotiator()
{
}

Negotiator::~Negotiator()
{
}

void Negotiator::AppendInput(char ch)
{
	m_inputBuffer.push(ch);
}

/**
*  Start(): Starts the negotiator controller; spawns the internal working thread
*
*	\param simulateExecTime : true to simulate processing time for Y and N
*/
void Negotiator::Start(bool simulateExecTime)
{
	if (simulateExecTime)
		m_execTime = std::chrono::milliseconds(100);

	m_workThread = std::thread(&Negotiator::WorkFunction, this);
}

/**
*  Stop(): Stops the negotiator controller; requests the working thread
*  to join the main process by adding 'q' to the input buffer
*/
void Negotiator::Stop()
{
	//push a 'q' letter to stop thread execution
	AppendInput('q');

	//wait for the entire input buffer to be processed
	std::cout << "Program terminated - waiting for summary to be generated ..." << std::endl;
	if (m_workThread.joinable())
		m_workThread.join();
}

/**
*  GenerateSummary(): Generates text for the summary message
*/
std::string Negotiator::GenerateSummary()
{
	if (!m_inputBuffer.empty())
	{
		//wait for summary to be processed
		std::unique_lock<std::mutex> summary_lock(m_summaryMutex);
		m_summaryCondition.wait(summary_lock);
	}

	return m_ngtData.Summary();
}

/**
 *  GenerateHelpText(): Generates text for the help message
 */
std::string Negotiator::GenerateHelpText()
{
	std::stringstream strStream;
	strStream << "Help v"
		<< SETestKCL_VERSION_MAJOR << "."
		<< SETestKCL_VERSION_MINOR << "."
		<< SETestKCL_VERSION_PATCH << std::endl
		<< "***************************************" << std::endl
		<< "This software counts the numbers of 'Yes's and 'No's during a negotiation."
		<< std::endl
		<< "Please refer below for a list of input keys to be used."
		<< std::endl << std::endl
		<< "Key" << std::endl << "------------" << std::endl
		<< "'y' or 'Y' : when you hear Yes to increase the count of `yes's" << std::endl
		<< "'n' or 'N' : when you hear No to increase the count of `no's" << std::endl
		<< "'z' or 'Z' : undos the last 'yes' or 'no' operation" << std::endl
		<< "'s' or 'S' : display a summary of the count so far" << std::endl
		<< "'q' or 'Q' : exits the programe, displaying a summary of the results" << std::endl
		<< "'h' or 'H' : displays this help message" << std::endl
		<< std::endl << std::endl;

	return strStream.str();
}

/**
*  WorkFunction(): The callable object to execute in the worker thread
*/
void Negotiator::WorkFunction()
{
	char ch;

	while (true)
	{
		//read a character from the input buffer
		ch = m_inputBuffer.pop();

		//end loop if it has been requested to quit the program
		if (ch == 'q')
			break;

		switch (ch)
		{
		case 'y':
			m_ngtData.m_numYes++;
			m_ngtData.m_lastWasYes = true;
			break;
		case 'n':
			m_ngtData.m_numNo++;
			m_ngtData.m_lastWasYes = false;
			break;
		case 'z':
			if (m_ngtData.m_lastWasYes)
				m_ngtData.m_numYes--;
			else
				m_ngtData.m_numNo--;
			break;
		case 's':
			//notify the GUI thread that summary is ready
			m_summaryCondition.notify_one();
			break;
		default:
			continue;
			break;
		}

		//simulate a fixed execution time for processing Y and N
		if (ch == 'y' || ch == 'n')
			std::this_thread::sleep_for(std::chrono::milliseconds(m_execTime));
	}
}
unsigned int Negotiator::GetNumberOfYes()
{
	return m_ngtData.m_numYes;
}

unsigned int Negotiator::GetNumberOfNo()
{
	return m_ngtData.m_numNo;
}
