#pragma once

#include <map>
#include <memory>
#include <cassert>
#include <string>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	ResourceHolder();
	void load(Identifier id, const std::string& filename);
	void load(Identifier id, std::unique_ptr<Resource>&& resource);
	Resource& getResource(Identifier id);
	const Resource& getResource(Identifier id) const;

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder()
	: mResourceMap()
{}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	auto uPtr = std::make_unique<Resource>();
	if (!uPtr->loadFromFile(filename))
		throw std::runtime_error("Could not find resource:" + filename);

	auto isInserted = mResourceMap.insert(std::make_pair(id, std::move(uPtr)));
	assert(isInserted.second);
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, std::unique_ptr<Resource>&& resource)
{
	auto isInserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(isInserted.second);
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::getResource(Identifier id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::getResource(Identifier id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}