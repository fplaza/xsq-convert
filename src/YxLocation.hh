#ifndef YX_LOCATION_HH
#define YX_LOCATION_HH

// (C) Copyright 2013-2014 INRA
// Use, modification and distribution is subject to the MIT License (MIT)
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)
#include <utility>

namespace Xsq
{
	class YxLocation
	{
	private:
		unsigned short* m_data;
		unsigned m_nb_locations;

	public:
		YxLocation(const H5::DataSet& yxLocation_ds)
		{
			hsize_t yxLocation_ds_dims[2];
			yxLocation_ds.getSpace().getSimpleExtentDims(
				yxLocation_ds_dims, NULL);

			m_nb_locations = yxLocation_ds_dims[0];

			m_data = new unsigned short[m_nb_locations*2];
			yxLocation_ds.read(
				m_data, H5::PredType::NATIVE_UINT16);
		};

		~YxLocation()
		{
			delete [] m_data;
		}

		std::pair<unsigned short, unsigned short> get_location(unsigned i) const
		{
			return std::make_pair(m_data[i*2], m_data[i*2+1]);
		}

		unsigned get_nb_locations() const
		{
			return m_nb_locations;
		}
	};
}

#endif // YX_LOCATION_HH
