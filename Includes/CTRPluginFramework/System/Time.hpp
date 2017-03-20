#ifndef CTRPLUGINFRAMEWORK_TIME_HPP
#define CTRPLUGINFRAMEWORK_TIME_HPP

namespace CTRPluginFramework
{
    class Time
    {
    public :

        Time(void);


        float   AsSeconds(void) const;

        int     AsMilliseconds(void) const;

        s64     AsMicroseconds(void) const;


        static const Time Zero; ///< Predefined "zero" time value

    private :

        friend      Time Seconds(float amount);
        friend      Time Milliseconds(int amount);
        friend      Time Microseconds(s64 amount);   

        explicit    Time(s64 microseconds);

    private :


        s64     _microseconds;
    };

  
    Time Seconds(float amount);

 
    Time Milliseconds(int amount);

 
    Time Microseconds(s64 amount);
 
    bool operator ==(Time left, Time right);

  
    bool operator !=(Time left, Time right);

 
    bool operator <(Time left, Time right);

 
    bool operator >(Time left, Time right);


    bool operator <=(Time left, Time right);


    bool operator >=(Time left, Time right);


    Time operator -(Time right);


    Time operator +(Time left, Time right);


    Time& operator +=(Time& left, Time right);


    Time operator -(Time left, Time right);


    Time& operator -=(Time& left, Time right);


    Time operator *(Time left, float right);


    Time operator *(Time left, s64 right);


    Time operator *(float left, Time right);


    Time operator *(s64 left, Time right);


    Time& operator *=(Time& left, float right);


    Time& operator *=(Time& left, s64 right);


    Time operator /(Time left, float right);


    Time operator /(Time left, s64 right);


    Time& operator /=(Time& left, float right);


    Time& operator /=(Time& left, s64 right);


    float operator /(Time left, Time right);


    Time operator %(Time left, Time right);


    Time& operator %=(Time& left, Time right);

}

#endif
