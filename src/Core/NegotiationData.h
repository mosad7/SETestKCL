#ifndef NEGOTIATION_DATA
#define NEGOTIATION_DATA

#include <sstream>
#include <chrono>
#include <iomanip>

/* Negotiation dataset */
struct NegotiationData
{
	unsigned int m_numYes;
	unsigned int m_numNo;
	bool m_lastWasYes;
	std::chrono::steady_clock::time_point m_startTime;
	std::chrono::steady_clock::time_point m_endTime;

	NegotiationData()
	{
		m_numYes = m_numNo = 0;
		m_startTime = std::chrono::steady_clock::now();
	}

	std::string Summary()
	{
		std::stringstream strStream;

		strStream << "   Summary" << std::endl
			<< "*************" << std::endl
			<< std::endl;

		m_endTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = m_endTime - m_startTime;
		double t_sec = elapsed_seconds.count();
		double t_mins = elapsed_seconds.count() / 60.0;
		double t_hrs = elapsed_seconds.count() / 3600.0;
		
		strStream << " Elapsed time: " << int(t_hrs) << ":" 
			<< int(std::fmod(t_mins, 60.0)) << ":" << int(std::fmod(t_sec, 60.0))
			<< std::endl << std::endl;

		//calculate number of Yes's per minute (avoid divide by zero)
		double yes_per_min = m_numYes / double(t_mins>0?t_mins:1);
		strStream << " YES : " << std::setw(7) << m_numYes << " @ " 
			<< std::setw(7) << std::fixed << std::setprecision(2)
			<< yes_per_min << "/minute" << std::endl;

		//calculate number of No's per minute
		double no_per_min = m_numNo / double(t_mins>0 ? t_mins : 1);
		strStream << " No  : " << std::setw(7) << m_numNo << " @ "
			<< std::setw(7) << std::fixed << std::setprecision(2)
			<< no_per_min << "/minute" << std::endl << std::endl;

		//calculate the ratio between Yes and No numbers
		double total_yes_no = m_numYes + m_numNo;
		double yes_no_ratio = m_numYes / (total_yes_no>0 ? total_yes_no : 1);
		strStream << " Expected negotiation sucess rate : " <<
			std::setw(4) << std::fixed << std::setprecision(2) << yes_no_ratio;

		return strStream.str();
	}
};

#endif //NEGOTIATION_DATA