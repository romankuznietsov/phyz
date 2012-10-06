#ifndef TIME_H
#define TIME_H


class Time
{
	private:
		float _value;

	public:
		inline Time() :
			_value(0.0f)
		{};


		inline Time(float value) :
			_value(value)
		{};


		inline Time(int value) :
			_value(value)
		{};


		inline operator float()
		{
			return _value;
		};


		inline int toInt() const
		{
			return _value;
		};
};


#endif // TIME_H
