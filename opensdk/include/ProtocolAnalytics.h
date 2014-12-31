#ifndef __OPENSDK_PROTOCOL_ANALYTICS_H__
#define __OPENSDK_PROTOCOL_ANALYTICS_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace opensdk {

typedef std::pair< std::string, std::string >   LogEventParamPair;
typedef std::map< std::string, std::string >    LogEventParamMap;

class ProtocolAnalytics : public PluginProtocol
{
public:
	ProtocolAnalytics();
	virtual ~ProtocolAnalytics();

	/**
     @brief Start a new session.
     @param appKey The identity of the application.
     */
	void startSession(const char* appKey);
    
	/**
     @brief Stop a session.
     @warning This interface only worked on android
     */
	void stopSession();

    /**
     @brief Set the timeout for expiring a session.
     @param millis In milliseconds as the unit of time.
     @note It must be invoked before calling startSession.
     */
	void setSessionContinueMillis(long millis);
    
    /**
     @brief log an error
     @param errorId The identity of error
     @param message Extern message for the error
     */
	void logError(const char* errorId, const char* message);
    
	/**
     @brief log an event.
     @param eventId The identity of event
     @param paramMap Extern parameters of the event, use NULL if not needed.
     */
	void logEvent(const char* eventId, LogEventParamMap* paramMap = NULL);
    
    /**
     @brief Track an event begin.
     @param eventId The identity of event
     */
    void logTimedEventBegin(const char* eventId);
    
    /**
     @brief Track an event end.
     @param eventId The identity of event
     */
	void logTimedEventEnd(const char* eventId);
    
	/**
     @brief Whether to catch uncaught exceptions to server.
     @warning This interface only worked on android.
     */
	void setCaptureUncaughtException(bool enabled);
};

} // namespace opensdk {


#endif /* __OPENSDK_PROTOCOL_ANALYTICS_H__ */
