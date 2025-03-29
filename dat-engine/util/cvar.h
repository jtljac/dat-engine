/*
 * Created using https://vkguide.dev/docs/extra-chapter/cvar_system/
 */

#pragma once

#include <cstdint>
#include <type_traits>
#include <util/string-utils.h>

#include "macros.h"
#include "type-traits.h"
namespace DatEngine {
    struct CVarParameter;

    /**
     * The category that a CVar belongs to
     */
    enum class CVarCategory : uint8_t {
        General,
        Graphics,
        Networking
    };

    /**
     * Flags that describe the behaviour of a CVar
     */
    enum class CVarFlags : uint16_t {
        None = 0b00000000,
        /** Enforces that the CVar cannot change value */
        ReadOnly = 0b00000001,
        /** Denotes the CVar is for debug purposes */
        Debug = 0b00000010,
        /** Suggests the CVar should be replicated from server to client */
        Replicated = 0b00000100,
        /** Suggests the CVar can be written to disk on change with a call*/
        Persistent = 0b00001000,
        /** Suggests that changes to the CVar will not be reflected until after a restart, force enables {@link Persistent} flag */
        RequiresRestart = 0b00011000
    };
    ENUM_FLAGS(CVarFlags);

    /**
     * Singleton Class responsible for handling the CVar System
     *
     * Implementation can be found in {@link CVarSystemImpl}, which is declared in CVar.cpp to reduce the public interface
     *
     * @see CVarSystemImpl
     */
    class CVarSystem {
    protected:
        ~CVarSystem() = default;

    public:
        /**
         * Get the CVar System instance
         * @return The singleton instance of the CVarSystem
         */
        static CVarSystem* get();
        /**
         * Get a CVar by its name hash
         *
         * @param hash The string hash of the CVar to lookup
         * @return The CVarParameter representing the CVar
         */
        virtual CVarParameter* getCVar(StringUtils::StringHash hash) = 0;

        /**
         * Create a new Integer CVar
         *
         * @param name The name of the CVar
         * @param description The description of the CVar
         * @param category The category of the CVar
         * @param value The value of the CVar
         * @return A CVarParameter Representing the CVar
         */
        virtual CVarParameter* createIntCVar(const char* name, const char* description, CVarCategory category, int32_t value) = 0;

        /**
         * Create a new Integer CVar
         *
         * @param name The name of the CVar
         * @param description The description of the CVar
         * @param category The category of the CVar
         * @param initialValue The initial value of the CVar
         * @param value The value of the CVar
         * @return A CVarParameter Representing the CVar
         */
        virtual CVarParameter* createIntCVar(const char* name, const char* description, CVarCategory category, int32_t initialValue, int32_t value) = 0;

        /**
         * Create a new Boolean CVar
         *
         * @param name The name of the CVar
         * @param description The description of the CVar
         * @param category The category of the CVar
         * @param value The value of the CVar
         * @return A CVarParameter Representing the CVar
         */
        virtual CVarParameter* createBoolCVar(const char* name, const char* description, CVarCategory category, bool value) = 0;

        /**
         * Create a new Boolean CVar
         *
         * @param name The name of the CVar
         * @param description The description of the CVar
         * @param category The category of the CVar
         * @param initialValue The initial value of the CVar
         * @param value The value of the CVar
         * @return A CVarParameter Representing the CVar
         */
        virtual CVarParameter* createBoolCVar(const char* name, const char* description, CVarCategory category, bool initialValue, bool value) = 0;

        /**
         * Create a new Float CVar
         *
         * @param name The name of the CVar
         * @param description The description of the CVar
         * @param category The category of the CVar
         * @param value The value of the CVar
         * @return A CVarParameter Representing the CVar
         */
        virtual CVarParameter* createFloatCVar(const char* name, const char* description, CVarCategory category, double value) = 0;

        /**
         * Create a new Float CVar
         *
         * @param name The name of the CVar
         * @param description The description of the CVar
         * @param category The category of the CVar
         * @param initialValue The initial value of the CVar
         * @param value The value of the CVar
         * @return A CVarParameter Representing the CVar
         */
        virtual CVarParameter* createFloatCVar(const char* name, const char* description, CVarCategory category, double initialValue, double value) = 0;

        /**
         * Create a new String CVar
         *
         * @param name The name of the CVar
         * @param description The description of the CVar
         * @param category The category of the CVar
         * @param value The value of the CVar
         * @return A CVarParameter Representing the CVar
         */
        virtual CVarParameter* createStringCVar(const char* name, const char* description, CVarCategory category, const char* value) = 0;

        /**
         * Create a new String CVar
         *
         * @param name The name of the CVar
         * @param description The description of the CVar
         * @param category The category of the CVar
         * @param initialValue The initial value of the CVar
         * @param value The value of the CVar
         * @return A CVarParameter Representing the CVar
         */
        virtual CVarParameter* createStringCVar(const char* name, const char* description, CVarCategory category, const char* initialValue, const char* value) = 0;

        /**
         * Get the value of an Integer CVar by its hash
         *
         * @param hash The hash of the CVar to get
         * @return A pointer to the value of the CVar with the given hash
         */
        virtual int32_t* getIntCVar(StringUtils::StringHash hash) = 0;
        /**
         * Set the value of an Integer CVar
         *
         * @param hash The hash of the CVar to set
         * @param value The value to set the CVar to
         */
        virtual void setIntCVar(StringUtils::StringHash hash, int32_t value) = 0;
        /**
         * Get the value of a Boolean CVar by its hash
         *
         * @param hash The hash of the CVar to get
         * @return A pointer to the value of the CVar with the given hash
         */
        virtual bool* getBoolCVar(StringUtils::StringHash hash) = 0;
        /**
         * Set the value of a Boolean CVar
         *
         * @param hash The hash of the CVar to set
         * @param value The value to set the CVar to
         */
        virtual void setBoolCVar(StringUtils::StringHash hash, bool value) = 0;

        /**
         * Get the value of a Float CVar by its hash
         *
         * @param hash The hash of the CVar to get
         * @return A pointer to the value of the CVar with the given hash
         */
        virtual double* getFloatCVar(StringUtils::StringHash hash) = 0;
        /**
         * Set the value of a Float CVar
         *
         * @param hash The has of the CVar to set
         * @param value The value to set the CVar to
         */
        virtual void setFloatCVar(StringUtils::StringHash hash, double value) = 0;

        /**
         * Get the value of a String CVar by its hash
         *
         * @param hash The hash of the CVar to get
         * @return A pointer to the value of the CVar with the given hash
         */
        virtual std::string* getStringCVar(StringUtils::StringHash hash) = 0;
        /**
         * Set the value of a String CVar
         *
         * @param hash The has of the CVar to set
         * @param value The value to set the CVar to
         */
        virtual void setStringCVar(StringUtils::StringHash hash, const char* value) = 0;
    };

    /**
     * Base class for Automatic CVar Registration
     *
     * This should not be used directly, instead one of the specific child classes should be used.
     *
     * @tparam T The type of the CVar
     *
     * @see CVarInt
     * @see CVarBool
     * @see CVarFloat
     * @see CVarString
     * @see CVarEnum
     */
    template <typename T>
    struct CVar {
    protected:
        /** The index of the CVar in it's CVarArray */
        uint32_t index = 0;
        using cvarType = T;
    public:
        virtual ~CVar() = default;
        /**
         * get the value of the CVar
         * @return The current value of the CVar
         */
        virtual T get() = 0;
        /**
         * Get the default value of the CVar
         * @return The default value of the CVar
         */
        virtual T getDefault() = 0;
        /**
         * Get a pointer to the value of the CVar
         * @return A pointer to the CVar value
         */
        virtual T* getPtr() = 0;
        /**
         * Set the value of the CVar
         * @param value The new value of the CVar
         */
        virtual void set(T value) = 0;
        /**
         * Reset the CVar to it's default value
         * @return The new value of the CVar
         */
        virtual T reset() = 0;
    };

    /**
     * CVar Specialisation for Integer values
     */
    struct CVarInt : CVar<int32_t> {
        CVarInt(const char* name, const char* description, CVarCategory category, int defaultValue, CVarFlags flags = CVarFlags::None);
        CVarInt(const char* name, const char* description, CVarCategory category, int value, int defaultValue, CVarFlags flags = CVarFlags::None);

        int get() override;
        int getDefault() override;
        int* getPtr() override;
        void set(int value) override;
        int reset() override;
    };

    /**
     * CVar Specialisation for Boolean values
     */
    struct CVarBool : CVar<bool> {
        CVarBool(const char* name, const char* description, CVarCategory category, bool defaultValue, CVarFlags flags = CVarFlags::None);
        CVarBool(const char* name, const char* description, CVarCategory category, bool value, bool defaultValue, CVarFlags flags = CVarFlags::None);

        bool get() override;
        bool getDefault() override;
        bool* getPtr() override;
        void set(bool value) override;
        bool reset() override;
    };

    /**
     * CVar Specialisation for floating point values
     */
    struct CVarFloat : CVar<double> {
        CVarFloat(const char* name, const char* description, CVarCategory category, double defaultValue, CVarFlags flags = CVarFlags::None);
        CVarFloat(const char* name, const char* description, CVarCategory category, double value, double defaultValue,
                  CVarFlags flags = CVarFlags::None);

        /**
         * Get the CVar value as a float instead of a double
         * @return The CVar value as a float
         */
        float getFloat();

        double get() override;
        double getDefault() override;
        double* getPtr() override;
        void set(double value) override;
        double reset() override;
    };

    /**
     * CVar Specialisation for String values
     */
    struct CVarString : CVar<std::string> {
        CVarString(const char* name, const char* description, CVarCategory category, const char* defaultValue, CVarFlags flags = CVarFlags::None);
        CVarString(const char* name, const char* description, CVarCategory category, const char* value, const char* defaultValue,
                   CVarFlags flags = CVarFlags::None);

        std::string get() override;
        std::string getDefault() override;
        std::string* getPtr() override;
        void set(std::string value) override;
        std::string reset() override;
    };

    /**
     * CVar Specialisation for Integer Enum Types
     * @tparam T The intergral enum to represent
     */
    template <integralEnumType T>
    struct CVarEnum : CVarInt {
        CVarEnum(const char* name, const char* description, const CVarCategory category, T defaultValue, const CVarFlags flags = CVarFlags::None) :
            CVarInt(name, description, category, static_cast<int32_t>(defaultValue), flags) {}
        CVarEnum(const char* name, const char* description, T value, const CVarCategory category, T defaultValue, const CVarFlags flags = CVarFlags::None) :
            CVarInt(name, description, category, static_cast<int32_t>(value), static_cast<int32_t>(defaultValue), flags) {}

        /**
         * Get the value stored in the CVar as the enum type
         * @return The enum value stored in the CVar
         */
        T getEnum() {
            return static_cast<T>(CVarInt::get());
        }

        /**
         * Get the default value stored in the CVar as the enum type
         * @return The default enum value stored in the CVar
         */
        T getDefaultEnum() {
            return static_cast<T>(CVarInt::getDefault());
        }

        /**
         * Set the value of the CVar using the enum representation
         * @param value The new value of the CVar
         */
        void set(T value) {
            CVarInt::set(static_cast<int32_t>(value));
        }

        /**
         * Reset the CVar value to it's default and return the Enum representation
         * @return T The new enum value stored in the CVar
         */
        T resetEnum() {
            return static_cast<T>(CVarInt::reset());
        }
    };
}