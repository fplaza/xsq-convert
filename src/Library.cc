// (C) Copyright 2013-2015 INRA
// Use, modification and distribution is subject to the MIT License (MIT)
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#include "Library.hh"
using namespace Xsq;
Library::Library(const std::string& name, const H5::Group& group)
	: m_complete_name(name), m_group(group)
{
	const H5::Attribute& sample_name_attribute = m_group.openAttribute("LibraryName");
	const H5::DataType& sample_name_type = sample_name_attribute.getDataType();
	sample_name_attribute.read(sample_name_type, m_sample_name);
}
std::vector<Tile>  Library::get_tiles() const
{
	std::vector<Tile> tiles;

	unsigned nb_tiles = m_group.getNumObjs();
	tiles.reserve(nb_tiles);
		
	for (unsigned tile_id = 0; tile_id < nb_tiles; tile_id++)
	{
		const std::string& tile_name = m_group.getObjnameByIdx(tile_id);
		tiles.push_back(Tile(tile_name, m_group.openGroup(tile_name)));
	}
		
	return tiles;
}
