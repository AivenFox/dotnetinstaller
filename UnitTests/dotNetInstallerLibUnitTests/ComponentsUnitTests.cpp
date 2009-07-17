#include "StdAfx.h"
#include "ComponentsUnitTests.h"

CPPUNIT_TEST_SUITE_REGISTRATION(DVLib::UnitTests::ComponentsUnitTests);

using namespace DVLib::UnitTests;

void ComponentsUnitTests::testAdd()
{
	Components components;
	ComponentPtr component1(new CmdComponent());
	component1->description = DVLib::GenerateGUIDStringW();
	ComponentPtr component2(new CmdComponent());
	component2->description = DVLib::GenerateGUIDStringW();
	components.add(component1);
	components.add(component2);
	CPPUNIT_ASSERT(components.size() == 2);
	CPPUNIT_ASSERT(components.contains(component1->description));
	CPPUNIT_ASSERT(components.contains(component2->description));
	CPPUNIT_ASSERT(! components.contains(DVLib::GenerateGUIDStringW()));
}

void ComponentsUnitTests::testOsFilters()
{
	Components components;
	ComponentPtr component1(new MsiComponent());
	component1->os_filter_greater = L"1";
	component1->os_filter_smaller = L"10";
	ComponentPtr component2(new MsiComponent());
	component2->os_filter_greater = L"10";
	component2->os_filter_smaller = L"100";
	ComponentPtr component3(new MsiComponent());
	component3->os_filter_greater = L"100";
	component3->os_filter_smaller = L"1000";
	components.add(component1);
	components.add(component2);
	components.add(component3);
	CPPUNIT_ASSERT(components.size() == 3);
	CPPUNIT_ASSERT(components.GetSupportedComponents(LcidUser).size() == 1);
}

void ComponentsUnitTests::testLcidFilters()
{
	Components components;
	ComponentPtr component_currentlcid(new MsiComponent());
	component_currentlcid->os_filter_lcid = L"1040";
	ComponentPtr component_anotherlcid(new MsiComponent());
	component_anotherlcid->os_filter_lcid = L"!1040";
	components.add(component_currentlcid);
	components.add(component_anotherlcid);
	CPPUNIT_ASSERT(components.size() == 2);
	CPPUNIT_ASSERT(components.GetSupportedComponents(LcidUser).size() == 1);
}

void ComponentsUnitTests::testPAFilters()
{
	Components components;
	ComponentPtr component_currentpa(new MsiComponent());
	component_currentpa->processor_architecture_filter = L"mips";
	ComponentPtr component_anotherpa(new MsiComponent());
	component_anotherpa->processor_architecture_filter = L"x86,x64";
	components.add(component_currentpa);
	components.add(component_anotherpa);
	CPPUNIT_ASSERT(components.size() == 2);
	CPPUNIT_ASSERT(components.GetSupportedComponents(LcidUser).size() == 1);
	CPPUNIT_ASSERT(get(components.GetSupportedComponents(LcidUser)[0]) == get(component_anotherpa));
}
