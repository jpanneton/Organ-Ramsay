#include "Component.h"

using namespace GUI;

Component::Component()
	: m_isSelected{ false }
	, m_isActivated{ false }
{
}

Component::~Component()
{
}

bool Component::isSelected() const
{
	return m_isSelected;
}

void Component::select()
{
	m_isSelected = true;
}

void Component::deselect()
{
	m_isSelected = false;
}

bool Component::isActivated() const
{
	return m_isActivated;
}

void Component::activate()
{
	m_isActivated = true;
}

void Component::deactivate()
{
	m_isActivated = false;
}