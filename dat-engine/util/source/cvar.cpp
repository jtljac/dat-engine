//
// Created by jacob on 22/07/24.
//
#include "../cvar.h"

#include <cassert>
#include <format>
#include <string>
#include <unordered_map>

#include <util/engine-constants.h>

using namespace DatEngine;

/* -------------------------------------------- */
/*  Internal CVar Stuff                         */
/* -------------------------------------------- */

/**
 * An enum representing the type of a CVar
 */
enum class CVarType : uint8_t {
    /** @link int32_t */
    INT,
    /** @c double */
    FLOAT,
    /** @link std::string */
    STRING
};

/**
 * Metadata about the CVar parameter
 */
struct DatEngine::CVarParameter {
    friend class CVarSystemImpl;

    /** The index of the CVar value in its type's {@link CVarArray} */
    uint32_t arrayIndex = 0;

    /** The type of the CVar */
    CVarType type;

    /** The flags of the CVar */
    CVarFlags flags = CVarFlags::None;

    /** A friendly name for the CVar, used for display and lookup */
    std::string name;
    /** A breif description of the CVar */
    std::string description;
};

/**
 * A structure containing the values of a CVar in storage
 * @tparam T The type being stored
 */
template<typename T>
struct CVarStorage {
    /** The initial value of the CVar */
    T initial{};
    /** The current value of the CVar */
    T current{};
    /** The parameters of the CVar */
    CVarParameter* parameter{};

    CVarStorage() = default;
};

/**
 * A container for storing CVars of a specific type
 * @tparam T The type of the CVars stored by this array
 */
template<typename T>
struct CVarArray {
    /**
     * A pointer to the raw array on the heap containing the cvars
     */
    CVarStorage<T>* const cvars;

    const size_t maxSize;

    /**
     * The next index available in the {@link cvars}
     */
    uint32_t lastCvar {0};

    CVarArray(const size_t size) : cvars(new CVarStorage<T>[size]), maxSize(size) {}

    ~CVarArray() {
        delete[] cvars;
    }

    /**
     * Get a full {@link CVarStorage} from the container
     * @param index The index of the CVar
     * @return The {@link CVarStorage} at the given index
     */
    CVarStorage<T>& getStorage(uint32_t index) {
        return cvars[index];
    }

    /**
     * Get the initial value of the CVar at the given index
     * @param index The index of the CVar
     * @return The initial value of the Cvar
     */
    T getInitial(const uint32_t index) {
        return getStorage(index).initial;
    }

    /**
     * Get the current value of the CVar at the given index
     * @param index The index of the CVar
     * @return The current value of the Cvar
     */
    T getCurrent(const uint32_t index) {
        return getStorage(index).current;
    }

    /**
     * Get the current value of the CVar at the given index
     * @param index The index of the CVar
     * @return The current value of the Cvar
     */
    T* getCurrentPtr(const uint32_t index) {
        return &(getStorage(index).current);
    }

    /**
     * Set the current value of the CVar at the given index
     * @param index The index of the CVar
     * @param val The value to set the CVar to
     */
    void setCurrent(const uint32_t index, const T& val) {
        getStorage(index).current = val;
    }

    /**
     * Reset the current value of the CVar to it's initial value
     * @param index The index of the CVar
     * @return The new value of the CVar
     */
    T reset(const uint32_t index) {
        CVarStorage<T> storage = getStorage(index);
        return storage.current = storage.initial;
    }

    /**
     * Add a new cvar to the CVar Array
     * @param initial The initial value of the CVar
     * @param value The current value of the CVar
     * @param param The CVar parameter
     * @return The index of the CVar in the array
     */
    uint32_t add(const T& initial, const T& value, CVarParameter* param) {
        assert(lastCvar < maxSize);

        cvars[lastCvar].initial = initial;
        cvars[lastCvar].current = value;
        cvars[lastCvar].parameter = param;

        param->arrayIndex = lastCvar;

        return lastCvar++;
    }

    /**
     * Add a new cvar to the CVar Array
     * @param value The current and initial value of the CVar
     * @param param The CVar parameter
     * @return The index of the CVar in the array
     */
    uint32_t add(const T& value, CVarParameter* param) {
        return add(value, value, param);
    }
};

/**
 * Private singleton implementation of CVar system
 */
class CVarSystemImpl final : public CVarSystem {
public:
    ~CVarSystemImpl() = default;

    /** The array containing Integer CVars */
    CVarArray<int32_t> intCVars{Constants::CVars::MAX_INTEGER};

    /** The array containing Float CVars */
    CVarArray<double> floatCVars{Constants::CVars::MAX_FLOAT};

    /** The array containing String CVars */
    CVarArray<std::string> stringCVars{Constants::CVars::MAX_STRING};

    /**
     * Get a {@link CVarArray} for the type \p T
     *
     * @tparam T The type of the CVar to get
     * @return The CVar array for the type
     */
    template<typename T>
    CVarArray<T>* getCVarArray();

    /**
     * Get a CVar from the CVar system
     * @param hash The Cvar Name
     * @return A pointer to the CVarParamter that stores the CVar values
     */
    CVarParameter* getCVar(StringUtils::StringHash hash) override;

    /**
     * Get the value of the CVar
     * @tparam T The type of the CVar Array
     * @param nameHash The name of the CVar
     * @return The current value of the CVar
     */
    template <typename T>
    T* getCVarCurrent(const StringUtils::StringHash nameHash) {
        CVarParameter* parameter = getCVar(nameHash);
        if (!parameter) return nullptr;

        return getCVarArray<T>()->getCurrentPtr(parameter->arrayIndex);
    }

    /**
     * Set the current value of the CVar
     * @tparam T The type of the CVar Array
     * @param nameHash The name of the CVar
     * @param value The new value of the CVar
     */
    template <typename T>
    void setCVarCurrent(const StringUtils::StringHash nameHash, const T& value) {
        CVarParameter* parameter = getCVar(nameHash);
        if (!parameter) return;

        getCVarArray<T>()->setCurrent(nameHash, value);
    }

    /**
     * Get an integer CVar by it's name
     * @param hash The name of the CVar
     * @return A pointer to the value of the CVar
     */
    int32_t* getIntCVar(StringUtils::StringHash hash) override;
    /**
     * Set the value of an integer CVar by it's name
     * @param hash The name of the CVar
     * @param value The new value of the CVar
     */
    void setIntCVar(StringUtils::StringHash hash, int32_t value) override;


    /**
     * Get a float CVar by it's name
     * @param hash The name of the CVar
     * @return A pointer to the value of the CVar
     */
    double* getFloatCVar(StringUtils::StringHash hash) override;
    /**
     * Set the value of a float CVar by it's name
     * @param hash The name of the CVar
     * @param value The new value of the CVar
     */
    void setFloatCVar(StringUtils::StringHash hash, double value) override;

    /**
     * Get a string CVar by it's name
     * @param hash The name of the CVar
     * @return A pointer to the value of the CVar
     */
    std::string* getStringCVar(StringUtils::StringHash hash) override;
    /**
     * Set the value of a string CVar by it's name
     * @param hash The name of the CVar
     * @param value The new value of the CVar
     */
    void setStringCVar(StringUtils::StringHash hash, const char* value) override;

    /**
     * Create a new Integer CVar
     * @param name The name of the CVar
     * @param description A description for the CVar
     * @param value The value of the CVar
     * @return A pointer to the CVarParameter
     */
    CVarParameter* createIntCVar(const char* name, const char* description, int32_t value) override;
    /**
     * Create a new Integer CVar with a default value
     * @param name The name of the CVar
     * @param description A description for the CVar
     * @param defaultValue The default value of the CVar
     * @param value The value of the CVar
     * @return A pointer to the CVarParameter
     */
    CVarParameter* createIntCVar(const char* name, const char* description, int32_t defaultValue, int32_t value) override;

    /**
     * Create a new Float CVar
     * @param name The name of the CVar
     * @param description A description for the CVar
     * @param value The value of the CVar
     * @return A pointer to the CVarParameter
     */
    CVarParameter* createFloatCVar(const char* name, const char* description, double value) override;
    /**
     * Create a new Float CVar with a default value
     * @param name The name of the CVar
     * @param description A description for the CVar
     * @param defaultValue The default value of the CVar
     * @param value The value of the CVar
     * @return A pointer to the CVarParameter
     */
    CVarParameter* createFloatCVar(const char* name, const char* description, double defaultValue, double value) override;

    /**
     * Create a new String CVar
     * @param name The name of the CVar
     * @param description A description for the CVar
     * @param value The value of the CVar
     * @return A pointer to the CVarParameter
     */
    CVarParameter* createStringCVar(const char* name, const char* description, const char* value) override;
    /**
     * Create a new String CVar with a default value
     * @param name The name of the CVar
     * @param description A description for the CVar
     * @param defaultValue The default value of the CVar
     * @param value The value of the CVar
     * @return A pointer to the CVarParameter
     */
    CVarParameter* createStringCVar(const char* name, const char* description, const char* defaultValue, const char* value) override;

    /**
     * Get the CVarSystem implementation, which grants access to hidden functios only accessabile in this file
     *
     * @return The CVarSystem implementation
     */
    static CVarSystemImpl* get() {
        return static_cast<CVarSystemImpl*>(CVarSystem::get());
    }
private:
    /**
     * Initialise a CVarParameter
     * @param name The name of the CVar
     * @param description The description of the CVar
     * @param type The type of the CVar
     * @return A pointer to a new CVar paramter
     */
    CVarParameter* initCvar(const char* name, const char* description, const CVarType& type);
    std::unordered_map<uint32_t, CVarParameter> savedCVars;
};

/* -------------------------------------------- */
/* CVar System                                  */
/* -------------------------------------------- */

CVarSystem* CVarSystem::get() {
    static ::CVarSystemImpl cvarSys{};
    return &cvarSys;
}


template<>
CVarArray<int32_t>* ::CVarSystemImpl::getCVarArray<int32_t>() {
    return &intCVars;
}

template<>
CVarArray<double>* ::CVarSystemImpl::getCVarArray<double>() {
    return &floatCVars;
}


template<>
CVarArray<std::string>* ::CVarSystemImpl::getCVarArray<std::string>() {
    return &stringCVars;
}

CVarParameter* ::CVarSystemImpl::getCVar(const StringUtils::StringHash hash) {
    const auto it = savedCVars.find(hash);

    if (it == savedCVars.end())
        return nullptr;

    return &(it->second);
}

/* -------------------------------------------- */
/*  CVar Parameter                              */
/* -------------------------------------------- */

int32_t* ::CVarSystemImpl::getIntCVar(const StringUtils::StringHash hash) {
    return getCVarCurrent<int32_t>(hash);
}

void ::CVarSystemImpl::setIntCVar(const StringUtils::StringHash hash, const int32_t value) {
    setCVarCurrent<int32_t>(hash, value);
}

double* ::CVarSystemImpl::getFloatCVar(const StringUtils::StringHash hash) {
    return getCVarCurrent<double>(hash);
}

void ::CVarSystemImpl::setFloatCVar(const StringUtils::StringHash hash, const double value) {
    setCVarCurrent<double>(hash, value);
}

std::string* ::CVarSystemImpl::getStringCVar(const StringUtils::StringHash hash) {
    return getCVarCurrent<std::string>(hash);
}

void ::CVarSystemImpl::setStringCVar(const StringUtils::StringHash hash, const char* value) {
    setCVarCurrent<std::string>(hash, value);
}

CVarParameter* ::CVarSystemImpl::createIntCVar(const char* name, const char* description, const int32_t value) {
    return createIntCVar(name, description, value, value);
}

CVarParameter* ::CVarSystemImpl::createIntCVar(const char* name, const char* description, const int32_t defaultValue, const int32_t value) {
    CVarParameter* param = initCvar(name, description, CVarType::INT);
    if (!param) return nullptr;

    getCVarArray<int32_t>()->add(defaultValue, value, param);

    return param;
}

CVarParameter* ::CVarSystemImpl::createFloatCVar(const char* name, const char* description, const double value) {
    return createFloatCVar(name, description, value, value);
}

CVarParameter* ::CVarSystemImpl::createFloatCVar(const char* name, const char* description, const double defaultValue, const double value) {
    CVarParameter* param = initCvar(name, description, CVarType::FLOAT);
    if (!param) return nullptr;

    getCVarArray<double>()->add(defaultValue, value, param);

    return param;
}

CVarParameter* ::CVarSystemImpl::createStringCVar(const char* name, const char* description, const char* value) {
    return createStringCVar(name, description, value, value);
}

CVarParameter* ::CVarSystemImpl::createStringCVar(const char* name, const char* description, const char* defaultValue, const char* value) {
    CVarParameter* param = initCvar(name, description, CVarType::STRING);
    if (!param) return nullptr;

    getCVarArray<std::string>()->add(defaultValue, value, param);

    return param;
}

CVarParameter* ::CVarSystemImpl::initCvar(const char* name, const char* description, const CVarType& type) {
    if (getCVar(name))
        return nullptr;

    const uint32_t nameHash = StringUtils::StringHash{name};
    savedCVars[nameHash] = CVarParameter();

    CVarParameter& newParameter = savedCVars[nameHash];

    newParameter.name = name;
    newParameter.description = description;
    newParameter.type = type;

    return &newParameter;
}

/* -------------------------------------------- */
/*  AutoCVar                                    */
/* -------------------------------------------- */

// Template functions
/**
 * Get the current value of a CVar by index
 * @tparam T The type of the CVar
 * @param index The index of the CVar
 * @return The current value of the CVar
 */
template <typename T>
T getCVarValueByIndex(const uint32_t index) {
    return ::CVarSystemImpl::get()->getCVarArray<T>()->getCurrent(index);
}

/**
 * Get the default value of a CVar by index
 * @tparam T The type of the CVar
 * @param index The index of the CVar
 * @return The default value of the CVar
 */
template <typename T>
T getCVarDefaultValueByIndex(const uint32_t index) {
    return ::CVarSystemImpl::get()->getCVarArray<T>()->getInitial(index);
}

/**
 * Get a pointer to the value of a CVar by index
 * @tparam T The type of the CVar
 * @param index The index of the CVar
 * @return The a pointer to the current value of the CVar
 */
template <typename T>
T* getCVarValuePtrByIndex(uint32_t index) {
    return ::CVarSystemImpl::get()->getCVarArray<T>()->getCurrentPtr(index);
}

/**
 * Set the value of a CVar by index
 * @tparam T The type of the CVar
 * @param index The index of the CVar
 * @param value The new value of the CVar
 */
template <typename T>
void setCVarValueByIndex(uint32_t index, T value) {
    ::CVarSystemImpl::get()->getCVarArray<T>()->setCurrent(index, value);
}

/**
 * Reset the value of a CVar to it's default
 * @tparam T The type of the CVar
 * @param index The index of the CVar
 * @return The new value of the CVar
 */
template <typename T>
T resetCVarValueByIndex(uint32_t index) {
    return ::CVarSystemImpl::get()->getCVarArray<T>()->reset(index);
}

// Int
CVarInt::CVarInt(const char* name, const char* description, const int defaultValue, const CVarFlags flags) {
    CVarParameter* cvar = CVarSystem::get()->createIntCVar(name, description, defaultValue);
    cvar->flags = flags;
    index = cvar->arrayIndex;
}

CVarInt::CVarInt(const char* name, const char* description, const int value, const int defaultValue,
                 const CVarFlags flags) {
    CVarParameter* cvar = CVarSystem::get()->createIntCVar(name, description, defaultValue, value);
    cvar->flags = flags;
    index = cvar->arrayIndex;
}

int32_t CVarInt::get() {
    return getCVarValueByIndex<cvarType>(index);
}

int32_t CVarInt::getDefault() {
    return getCVarDefaultValueByIndex<cvarType>(index);
}

int32_t* CVarInt::getPtr() {
    return getCVarValuePtrByIndex<cvarType>(index);
}

void CVarInt::set(const int32_t value) {
    setCVarValueByIndex<cvarType>(index, value);
}

int32_t CVarInt::reset() {
    return resetCVarValueByIndex<cvarType>(index);
}

// Double
CVarFloat::CVarFloat(const char* name, const char* description, const double defaultValue, const CVarFlags flags) {
    CVarParameter* cvar = CVarSystem::get()->createFloatCVar(name, description, defaultValue);
    cvar->flags = flags;
    index = cvar->arrayIndex;
}

CVarFloat::CVarFloat(const char* name, const char* description, const double value, const double defaultValue, const CVarFlags flags) {
    CVarParameter* cvar = CVarSystem::get()->createFloatCVar(name, description, defaultValue, value);
    cvar->flags = flags;
    index = cvar->arrayIndex;
}

float CVarFloat::getFloat() {
    return static_cast<float>(get());
}

double CVarFloat::get() {
    return getCVarValueByIndex<cvarType>(index);
}

double CVarFloat::getDefault() {
    return getCVarDefaultValueByIndex<cvarType>(index);
}

double* CVarFloat::getPtr() {
    return getCVarValuePtrByIndex<cvarType>(index);
}

void CVarFloat::set(double value) {
    setCVarValueByIndex<cvarType>(index, value);
}

double CVarFloat::reset() {
    return resetCVarValueByIndex<cvarType>(index);
}

// String
CVarString::CVarString(const char* name, const char* description, const char* defaultValue, const CVarFlags flags) {
    CVarParameter* cvar = CVarSystem::get()->createStringCVar(name, description, defaultValue);
    cvar->flags = flags;
    index = cvar->arrayIndex;
}

CVarString::CVarString(const char* name, const char* description, const char* value, const char* defaultValue, const CVarFlags flags) {
    CVarParameter* cvar = CVarSystem::get()->createStringCVar(name, description, defaultValue, value);
    cvar->flags = flags;
    index = cvar->arrayIndex;
}

std::string CVarString::get() {
    return getCVarValueByIndex<cvarType>(index);
}

std::string CVarString::getDefault() {
    return getCVarDefaultValueByIndex<cvarType>(index);
}

std::string* CVarString::getPtr() {
    return getCVarValuePtrByIndex<cvarType>(index);
}

void CVarString::set(std::string value) {
    setCVarValueByIndex<cvarType>(index, value);
}

std::string CVarString::reset() {
    return resetCVarValueByIndex<cvarType>(index);
}