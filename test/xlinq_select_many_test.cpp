#include <gtest/gtest.h>
#include "model/xlinq_test_model.h"
#include <xlinq/xlinq_from.h>
#include <xlinq/xlinq_select_many.h>
#include <array>

using namespace std;
using namespace xlinq;

TEST(XLinqSelectManyTest, FlatteningCollectionContainingVectorsPassedByReference)
{
	auto companies = getCompanies();
	auto allEmployees = from(companies) >> select_many([](Company& c) -> std::vector<Person>& { return c.employees; });
	auto enumerator = allEmployees >> getEnumerator();
	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Anna", enumerator->current().firstName);
	ASSERT_EQ("Walczak", enumerator->current().secondName);
	ASSERT_EQ(19, enumerator->current().age);
	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Lend", enumerator->current().secondName);
	ASSERT_EQ(33, enumerator->current().age);
	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Janusz", enumerator->current().firstName);
	ASSERT_EQ("Grzyb", enumerator->current().secondName);
	ASSERT_EQ(27, enumerator->current().age);
	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Marian", enumerator->current().firstName);
	ASSERT_EQ("Halbut", enumerator->current().secondName);
	ASSERT_EQ(31, enumerator->current().age);
	ASSERT_FALSE(enumerator->next());
}

TEST(XLinqSelectManyTest, FlatteningCollectionContainingVectorsCopied)
{
	auto companies = getCompanies();
	auto allEmployees = from(companies) >> select_many([](Company& c) { return c.employees; });
	auto enumerator = allEmployees >> getEnumerator();
	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Anna", enumerator->current().firstName);
	ASSERT_EQ("Walczak", enumerator->current().secondName);
	ASSERT_EQ(19, enumerator->current().age);
	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Lend", enumerator->current().secondName);
	ASSERT_EQ(33, enumerator->current().age);
	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Janusz", enumerator->current().firstName);
	ASSERT_EQ("Grzyb", enumerator->current().secondName);
	ASSERT_EQ(27, enumerator->current().age);
	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Marian", enumerator->current().firstName);
	ASSERT_EQ("Halbut", enumerator->current().secondName);
	ASSERT_EQ(31, enumerator->current().age);
	ASSERT_FALSE(enumerator->next());
}