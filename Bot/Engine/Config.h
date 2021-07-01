#pragma once
#include <string>
#include <type_traits>
namespace {
	template<typename T> std::enable_if_t<std::is_integral_v<T>, T> default_initializer() { return 0; }
	template<typename T> std::enable_if_t<std::is_floating_point_v<T>, T> default_initializer() { return 0.0; }
	template<typename T> std::enable_if_t<std::is_same_v<std::string, T>, T> default_initializer() { return ""; }
}

#define CONF_PROPERTY(__TYPE__, __NAME__,__VAR_NAME__) \
private: __TYPE__ __VAR_NAME__ = default_initializer<__TYPE__>();  \
public: __TYPE__ get##__NAME__() const {return __VAR_NAME__;} \
public: void set##__NAME__(__TYPE__ var){__VAR_NAME__ = var;}

#define ROB_PROPERTY(__NAME__, __ROB_VAR_NAME__)\
public: bool get##__NAME__() const {return robConfig.getGameVariable(__ROB_VAR_NAME__);}\
//public: void set##__NAME__(bool value) {robConfig.setGameVariable("#__ROB_VAR_NAME__", value);}


#define DDHR_CONF_WATERMARK "33301"
#define DDHR_CONF_SAFEMODE "33302"
#define DDHR_CONF_NO_DO "33303"
#define DDHR_CONF_NO_SYNC "33304"
#define DDHR_CONF_SYNC_NO_FADE "33305"

class ConfigRobProxy{
private:
	void* gmInstance;
	bool(__thiscall* gmGameVariable)(void* self, const char* key);
public:
	bool getGameVariable(const std::string& key) const;
	ConfigRobProxy();
};

class BotConfiguration {
private:
	ConfigRobProxy robConfig;
public:
	CONF_PROPERTY(std::string, MacroName, m_macroName);
	CONF_PROPERTY(bool, DeltaOverride, m_deltaOverride);
	CONF_PROPERTY(bool, Frozen, m_frozen);
	CONF_PROPERTY(short, FPS, m_fps);
	CONF_PROPERTY(double, Speed, m_speedMult);
	CONF_PROPERTY(bool, SuspendIO, m_suspendIO);

	ROB_PROPERTY(Watermark, DDHR_CONF_WATERMARK);
	ROB_PROPERTY(Safemode,  DDHR_CONF_SAFEMODE);
	ROB_PROPERTY(NoDeltaOverride, DDHR_CONF_NO_DO);
	ROB_PROPERTY(NoSyncLayer, DDHR_CONF_NO_SYNC);
	ROB_PROPERTY(NoSyncFadeout, DDHR_CONF_SYNC_NO_FADE);

	BotConfiguration();
};

//#undef CONF_PROPERTY

