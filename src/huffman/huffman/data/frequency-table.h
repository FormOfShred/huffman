#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H

#include <map>

namespace data
{
	template <typename T>
	class FrequencyTable
	{
		std::map<T, unsigned> freqTable;

	public:
		void increment(const T& x)
		{
			if (freqTable.find(x) == freqTable.end())
			{
				freqTable[x] = 1;
			}
			else
			{
				freqTable[x]++;
			}
		}

		unsigned operator[](const T& x) const
		{
			if (freqTable.find(x) == freqTable.end())
			{
				return 0;
			}
			else
			{
				return freqTable.at(x);
			}
		}

		std::vector<T> values() const
		{
			std::vector<T> values;
			for (auto it = freqTable.begin(); it != freqTable.end(); ++it)
			{
				values.push_back(it->first);
			}
			return values;
		}

		std::vector<std::pair<T, unsigned>> pairs()
		{
			std::vector<std::pair<T, unsigned>> pairs;
			for (auto const& it : freqTable) {
				pairs.push_back(std::pair<T, unsigned>(it.first, it.second));
			}
			return pairs;
		}
	};

	template <typename T>
	FrequencyTable<T> count_frequencies(std::vector<T> values)
	{
		FrequencyTable<T> freqTable;
		for (auto it = values.begin(); it != values.end(); ++it)
		{
			freqTable.increment(it);
		}
		return freqTable;
	};

}

#endif