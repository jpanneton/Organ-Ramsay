#pragma once

// Name: ResourceHolder.h
// Author: Jérémi Panneton
// Description: Resource holder class

#include <cassert> // Used in ResourceHolder.inl
#include <memory>
#include <unordered_map>

/// @brief Resource holder
/// @tparam Resource Type of resource (e.g. texture)
/// @tparam Identifier ID type for resource access (e.g. texture id)
/// @author Jeremi Panneton
/// @ingroup engine
template<class Resource, class Identifier>
class ResourceHolder
{
public:
	/// @brief Load a resource from disk to memory and associate it to a specified ID
	/// @param[in] id ID to associate with the resource
	/// @param[in] filename Resource path
	/// @param[in] parameters Additional parameters (optional)
	template<class... Parameters>
	void load(Identifier id, const std::string& filename, const Parameters&... parameters);

	/// @brief Get the resource associated with a specified ID
	/// @param[in] id ID associated with the resource
	/// @return Requested resource
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;

private:
	/// @brief Resource container
	std::unordered_map<Identifier, std::unique_ptr<Resource>> m_resourceMap;
};

#include "ResourceHolder.inl"