#include <gtest/gtest.h>
#include "model/xlinq_test_model.h"
#include <xlinq/xlinq_from_container_shared_ptr.h>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;
using namespace xlinq;

TEST(XLinqFromVectorSharedPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->current();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromVectorSharedPtrTest, CallBackBeforeEnumerationWasStarted)
{
	auto persons = getPersonsSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->back();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromVectorSharedPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->current();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromVectorSharedPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->next();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromVectorSharedPtrTest, RandomAccessEnumerableBegin)
{
	auto persons = getPersonsSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Piotr", enumerator->current().firstName);
	ASSERT_EQ("Kempa", enumerator->current().secondName);
	ASSERT_EQ(21, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Kania", enumerator->current().secondName);
	ASSERT_EQ(22, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Anna", enumerator->current().firstName);
	ASSERT_EQ("Ga��zka", enumerator->current().secondName);
	ASSERT_EQ(54, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Joanna", enumerator->current().firstName);
	ASSERT_EQ("Gwizd", enumerator->current().secondName);
	ASSERT_EQ(37, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Kamil", enumerator->current().firstName);
	ASSERT_EQ("Goryszewicz", enumerator->current().secondName);
	ASSERT_EQ(18, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Jan", enumerator->current().firstName);
	ASSERT_EQ("Lampus", enumerator->current().secondName);
	ASSERT_EQ(71, enumerator->current().age);

	ASSERT_FALSE(enumerator->next());

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Jan", enumerator->current().firstName);
	ASSERT_EQ("Lampus", enumerator->current().secondName);
	ASSERT_EQ(71, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Kamil", enumerator->current().firstName);
	ASSERT_EQ("Goryszewicz", enumerator->current().secondName);
	ASSERT_EQ(18, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Joanna", enumerator->current().firstName);
	ASSERT_EQ("Gwizd", enumerator->current().secondName);
	ASSERT_EQ(37, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Anna", enumerator->current().firstName);
	ASSERT_EQ("Ga��zka", enumerator->current().secondName);
	ASSERT_EQ(54, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Kania", enumerator->current().secondName);
	ASSERT_EQ(22, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Piotr", enumerator->current().firstName);
	ASSERT_EQ("Kempa", enumerator->current().secondName);
	ASSERT_EQ(21, enumerator->current().age);

	ASSERT_FALSE(enumerator->back());

	ASSERT_FALSE(enumerator->advance(7));

	ASSERT_TRUE(enumerator->advance(-4));
	ASSERT_EQ("Anna", enumerator->current().firstName);
	ASSERT_EQ("Ga��zka", enumerator->current().secondName);
	ASSERT_EQ(54, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Joanna", enumerator->current().firstName);
	ASSERT_EQ("Gwizd", enumerator->current().secondName);
	ASSERT_EQ(37, enumerator->current().age);

	ASSERT_TRUE(enumerator->advance(-2));
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Kania", enumerator->current().secondName);
	ASSERT_EQ(22, enumerator->current().age);

	ASSERT_TRUE(enumerator->advance(4));
	ASSERT_EQ("Jan", enumerator->current().firstName);
	ASSERT_EQ("Lampus", enumerator->current().secondName);
	ASSERT_EQ(71, enumerator->current().age);

	ASSERT_FALSE(enumerator->advance(-7));

	ASSERT_TRUE(enumerator->advance(6));
	ASSERT_EQ("Jan", enumerator->current().firstName);
	ASSERT_EQ("Lampus", enumerator->current().secondName);
	ASSERT_EQ(71, enumerator->current().age);
}

TEST(XLinqFromVectorSharedPtrTest, RandomAccessEnumerableEnd)
{
	auto persons = getPersonsSharedPtr();
	auto enumerator = from(persons) >> getEndEnumerator();

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Jan", enumerator->current().firstName);
	ASSERT_EQ("Lampus", enumerator->current().secondName);
	ASSERT_EQ(71, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Kamil", enumerator->current().firstName);
	ASSERT_EQ("Goryszewicz", enumerator->current().secondName);
	ASSERT_EQ(18, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Joanna", enumerator->current().firstName);
	ASSERT_EQ("Gwizd", enumerator->current().secondName);
	ASSERT_EQ(37, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Anna", enumerator->current().firstName);
	ASSERT_EQ("Ga��zka", enumerator->current().secondName);
	ASSERT_EQ(54, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Kania", enumerator->current().secondName);
	ASSERT_EQ(22, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Piotr", enumerator->current().firstName);
	ASSERT_EQ("Kempa", enumerator->current().secondName);
	ASSERT_EQ(21, enumerator->current().age);

	ASSERT_FALSE(enumerator->back());

	ASSERT_FALSE(enumerator->advance(7));

	ASSERT_TRUE(enumerator->advance(-4));
	ASSERT_EQ("Anna", enumerator->current().firstName);
	ASSERT_EQ("Ga��zka", enumerator->current().secondName);
	ASSERT_EQ(54, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Joanna", enumerator->current().firstName);
	ASSERT_EQ("Gwizd", enumerator->current().secondName);
	ASSERT_EQ(37, enumerator->current().age);

	ASSERT_TRUE(enumerator->advance(-2));
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Kania", enumerator->current().secondName);
	ASSERT_EQ(22, enumerator->current().age);

	ASSERT_TRUE(enumerator->advance(4));
	ASSERT_EQ("Jan", enumerator->current().firstName);
	ASSERT_EQ("Lampus", enumerator->current().secondName);
	ASSERT_EQ(71, enumerator->current().age);

	ASSERT_FALSE(enumerator->advance(-7));

	ASSERT_TRUE(enumerator->advance(6));
	ASSERT_EQ("Jan", enumerator->current().firstName);
	ASSERT_EQ("Lampus", enumerator->current().secondName);
	ASSERT_EQ(71, enumerator->current().age);
}

TEST(XLinqFromVectorSharedPtrTest, RandomAccessEnumerableAt)
{
	auto persons = getPersonsSharedPtr();
	auto enumerator = from(persons) >> getEnumeratorAt(2);

	ASSERT_EQ("Anna", enumerator->current().firstName);
	ASSERT_EQ("Ga��zka", enumerator->current().secondName);
	ASSERT_EQ(54, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Kania", enumerator->current().secondName);
	ASSERT_EQ(22, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Piotr", enumerator->current().firstName);
	ASSERT_EQ("Kempa", enumerator->current().secondName);
	ASSERT_EQ(21, enumerator->current().age);

	ASSERT_FALSE(enumerator->back());

	ASSERT_FALSE(enumerator->advance(7));

	ASSERT_TRUE(enumerator->advance(-4));
	ASSERT_EQ("Anna", enumerator->current().firstName);
	ASSERT_EQ("Ga��zka", enumerator->current().secondName);
	ASSERT_EQ(54, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Joanna", enumerator->current().firstName);
	ASSERT_EQ("Gwizd", enumerator->current().secondName);
	ASSERT_EQ(37, enumerator->current().age);

	ASSERT_TRUE(enumerator->advance(-2));
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Kania", enumerator->current().secondName);
	ASSERT_EQ(22, enumerator->current().age);

	ASSERT_TRUE(enumerator->advance(4));
	ASSERT_EQ("Jan", enumerator->current().firstName);
	ASSERT_EQ("Lampus", enumerator->current().secondName);
	ASSERT_EQ(71, enumerator->current().age);

	ASSERT_FALSE(enumerator->advance(-7));

	ASSERT_TRUE(enumerator->advance(6));
	ASSERT_EQ("Jan", enumerator->current().firstName);
	ASSERT_EQ("Lampus", enumerator->current().secondName);
	ASSERT_EQ(71, enumerator->current().age);
}

TEST(XLinqFromVectorSharedPtrTest, RandomAccessEnumerableEmpty)
{
	typedef std::vector<int> tcontainer;
	std::shared_ptr<tcontainer> container(new tcontainer());
	ASSERT_FALSE((from(container) >> getEnumerator())->next());
	ASSERT_FALSE((from(container) >> getEndEnumerator())->back());
	ASSERT_FALSE((from(container) >> getEnumerator())->advance(1));
	ASSERT_FALSE((from(container) >> getEnumerator())->advance(-1));
}

TEST(XLinqFromVectorSharedPtrTest, RandomAccessEnumerableSize)
{
	auto persons = getPersonsSharedPtr();
	ASSERT_EQ(6, from(persons)->size());
}

TEST(XLinqFromVectorSharedPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();

	ASSERT_TRUE(enumerator->next());
	auto second = enumerator->clone();
	ASSERT_TRUE(enumerator->equals(second));
	ASSERT_TRUE(enumerator->next());
	ASSERT_FALSE(enumerator->equals(second));
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Piotr", second->current().firstName);

	while (enumerator->next());

	ASSERT_EQ("Piotr", second->current().firstName);
	ASSERT_TRUE(second->next());
	ASSERT_EQ("Micha�", second->current().firstName);
}

TEST(XLinqFromVectorSharedPtrTest, DistanceLtGtTest)
{
	auto persons = getPersonsSharedPtr();
	auto enumerable = from(persons);
	auto it = enumerable >> getEnumerator();
	auto end = enumerable >> getEndEnumerator();

	ASSERT_FALSE(it->equals(end));
	ASSERT_TRUE(it->less_than(end));
	ASSERT_FALSE(end->less_than(it));
	ASSERT_FALSE(it->greater_than(end));
	ASSERT_TRUE(end->greater_than(it));

	ASSERT_EQ(enumerable->size() + 1, it->distance_to(end));
	ASSERT_EQ(-(enumerable->size() + 1), end->distance_to(it));

	ASSERT_TRUE(it->next());

	ASSERT_FALSE(it->equals(end));
	ASSERT_TRUE(it->less_than(end));
	ASSERT_FALSE(end->less_than(it));
	ASSERT_FALSE(it->greater_than(end));
	ASSERT_TRUE(end->greater_than(it));

	ASSERT_EQ(enumerable->size(), it->distance_to(end));
	ASSERT_EQ(-enumerable->size(), end->distance_to(it));

	auto itc = std::dynamic_pointer_cast<IRandomAccessEnumerator<Person>>(it->clone());

	ASSERT_TRUE(it->equals(itc));
	ASSERT_FALSE(it->less_than(itc));
	ASSERT_FALSE(itc->less_than(it));
	ASSERT_FALSE(it->greater_than(itc));
	ASSERT_FALSE(itc->greater_than(it));

	ASSERT_EQ(0, it->distance_to(itc));
	ASSERT_EQ(0, itc->distance_to(it));

	ASSERT_TRUE(end->back());

	ASSERT_FALSE(it->equals(end));
	ASSERT_TRUE(it->less_than(end));
	ASSERT_FALSE(end->less_than(it));
	ASSERT_FALSE(it->greater_than(end));
	ASSERT_TRUE(end->greater_than(it));

	ASSERT_EQ(enumerable->size() - 1, it->distance_to(end));
	ASSERT_EQ(-(enumerable->size() - 1), end->distance_to(it));

	ASSERT_TRUE(it->advance(it->distance_to(end)));

	ASSERT_TRUE(it->equals(end));
	ASSERT_FALSE(it->less_than(end));
	ASSERT_FALSE(end->less_than(it));
	ASSERT_FALSE(it->greater_than(end));
	ASSERT_FALSE(end->greater_than(it));

	ASSERT_EQ(0, it->distance_to(end));
	ASSERT_EQ(0, end->distance_to(it));
}

TEST(XLinqFromListSharedPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsListSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->current();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromListSharedPtrTest, CallBackBeforeEnumerationWasStarted)
{
	auto persons = getPersonsListSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->back();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromListSharedPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsListSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->current();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromListSharedPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsListSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->next();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromListSharedPtrTest, BidirectionalEnumerableBegin)
{
	auto persons = getPersonsListSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Piotr", enumerator->current().firstName);
	ASSERT_EQ("Kempa", enumerator->current().secondName);
	ASSERT_EQ(21, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Kania", enumerator->current().secondName);
	ASSERT_EQ(22, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Anna", enumerator->current().firstName);
	ASSERT_EQ("Ga��zka", enumerator->current().secondName);
	ASSERT_EQ(54, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Joanna", enumerator->current().firstName);
	ASSERT_EQ("Gwizd", enumerator->current().secondName);
	ASSERT_EQ(37, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Kamil", enumerator->current().firstName);
	ASSERT_EQ("Goryszewicz", enumerator->current().secondName);
	ASSERT_EQ(18, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Jan", enumerator->current().firstName);
	ASSERT_EQ("Lampus", enumerator->current().secondName);
	ASSERT_EQ(71, enumerator->current().age);

	ASSERT_FALSE(enumerator->next());

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Jan", enumerator->current().firstName);
	ASSERT_EQ("Lampus", enumerator->current().secondName);
	ASSERT_EQ(71, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Kamil", enumerator->current().firstName);
	ASSERT_EQ("Goryszewicz", enumerator->current().secondName);
	ASSERT_EQ(18, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Joanna", enumerator->current().firstName);
	ASSERT_EQ("Gwizd", enumerator->current().secondName);
	ASSERT_EQ(37, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Anna", enumerator->current().firstName);
	ASSERT_EQ("Ga��zka", enumerator->current().secondName);
	ASSERT_EQ(54, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Kania", enumerator->current().secondName);
	ASSERT_EQ(22, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Piotr", enumerator->current().firstName);
	ASSERT_EQ("Kempa", enumerator->current().secondName);
	ASSERT_EQ(21, enumerator->current().age);

	ASSERT_FALSE(enumerator->back());
}

TEST(XLinqFromListSharedPtrTest, BidirectionalEnumerableEnd)
{
	auto persons = getPersonsListSharedPtr();
	auto enumerator = from(persons) >> getEndEnumerator();

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Jan", enumerator->current().firstName);
	ASSERT_EQ("Lampus", enumerator->current().secondName);
	ASSERT_EQ(71, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Kamil", enumerator->current().firstName);
	ASSERT_EQ("Goryszewicz", enumerator->current().secondName);
	ASSERT_EQ(18, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Joanna", enumerator->current().firstName);
	ASSERT_EQ("Gwizd", enumerator->current().secondName);
	ASSERT_EQ(37, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Anna", enumerator->current().firstName);
	ASSERT_EQ("Ga��zka", enumerator->current().secondName);
	ASSERT_EQ(54, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Kania", enumerator->current().secondName);
	ASSERT_EQ(22, enumerator->current().age);

	ASSERT_TRUE(enumerator->back());
	ASSERT_EQ("Piotr", enumerator->current().firstName);
	ASSERT_EQ("Kempa", enumerator->current().secondName);
	ASSERT_EQ(21, enumerator->current().age);

	ASSERT_FALSE(enumerator->back());
}

TEST(XLinqFromListSharedPtrTest, BidirectionalEnumerableEmpty)
{
	typedef std::list<int> tcontainer;
	std::shared_ptr<tcontainer> container(new tcontainer());
	ASSERT_FALSE((from(container) >> getEnumerator())->next());
	ASSERT_FALSE((from(container) >> getEndEnumerator())->back());
}

TEST(XLinqFromListSharedPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsListSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();

	ASSERT_TRUE(enumerator->next());
	auto second = enumerator->clone();
	ASSERT_TRUE(enumerator->equals(second));
	ASSERT_TRUE(enumerator->next());
	ASSERT_FALSE(enumerator->equals(second));
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Piotr", second->current().firstName);

	while (enumerator->next());

	ASSERT_EQ("Piotr", second->current().firstName);
	ASSERT_TRUE(second->next());
	ASSERT_EQ("Micha�", second->current().firstName);
}

TEST(XLinqFromForwardListSharedPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsForwardListSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->current();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromForwardListSharedPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsForwardListSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->current();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromForwardListSharedPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsForwardListSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->next();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromForwardListSharedPtrTest, EnumerableBegin)
{
	auto persons = getPersonsForwardListSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Piotr", enumerator->current().firstName);
	ASSERT_EQ("Kempa", enumerator->current().secondName);
	ASSERT_EQ(21, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Kania", enumerator->current().secondName);
	ASSERT_EQ(22, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Anna", enumerator->current().firstName);
	ASSERT_EQ("Ga��zka", enumerator->current().secondName);
	ASSERT_EQ(54, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Joanna", enumerator->current().firstName);
	ASSERT_EQ("Gwizd", enumerator->current().secondName);
	ASSERT_EQ(37, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Kamil", enumerator->current().firstName);
	ASSERT_EQ("Goryszewicz", enumerator->current().secondName);
	ASSERT_EQ(18, enumerator->current().age);

	ASSERT_TRUE(enumerator->next());
	ASSERT_EQ("Jan", enumerator->current().firstName);
	ASSERT_EQ("Lampus", enumerator->current().secondName);
	ASSERT_EQ(71, enumerator->current().age);

	ASSERT_FALSE(enumerator->next());
}

TEST(XLinqFromForwardListSharedPtrTest, EnumerableEmpty)
{
	typedef std::forward_list<int> tcontainer;
	std::shared_ptr<tcontainer> container(new tcontainer());
	ASSERT_FALSE((from(container) >> getEnumerator())->next());
}

TEST(XLinqFromForwardListSharedPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsForwardListSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();

	ASSERT_TRUE(enumerator->next());
	auto second = enumerator->clone();
	ASSERT_TRUE(enumerator->equals(second));
	ASSERT_TRUE(enumerator->next());
	ASSERT_FALSE(enumerator->equals(second));
	ASSERT_EQ("Micha�", enumerator->current().firstName);
	ASSERT_EQ("Piotr", second->current().firstName);

	while (enumerator->next());

	ASSERT_EQ("Piotr", second->current().firstName);
	ASSERT_TRUE(second->next());
	ASSERT_EQ("Micha�", second->current().firstName);
}

TEST(XLinqFromSetSharedPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->current();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromSetSharedPtrTest, CallBackBeforeEnumerationWasStarted)
{
	auto persons = getPersonsSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->back();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromSetSharedPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->current();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromSetSharedPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->next();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromSetSharedPtrTest, BidirectionalEnumerableBegin)
{
	auto persons = getPersonsSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	std::set<Person> occuredPersons;

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_FALSE(enumerator->next());
	ASSERT_EQ(6, occuredPersons.size());

	occuredPersons.clear();
	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_FALSE(enumerator->back());
	ASSERT_EQ(6, occuredPersons.size());
}

TEST(XLinqFromSetSharedPtrTest, BidirectionalEnumerableEnd)
{
	auto persons = getPersonsSetSharedPtr();
	auto enumerator = from(persons) >> getEndEnumerator();
	std::set<Person> occuredPersons;

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_FALSE(enumerator->back());
	ASSERT_EQ(6, occuredPersons.size());

	occuredPersons.clear();
}

TEST(XLinqFromSetSharedPtrTest, BidirectionalEnumerableEmpty)
{
	typedef std::set<int> tcontainer;
	std::shared_ptr<tcontainer> container(new tcontainer());
	ASSERT_FALSE((from(container) >> getEnumerator())->next());
	ASSERT_FALSE((from(container) >> getEndEnumerator())->back());
}

TEST(XLinqFromSetSharedPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();

	ASSERT_TRUE(enumerator->next());
	string fName = enumerator->current().firstName;
	auto second = enumerator->clone();
	ASSERT_TRUE(enumerator->equals(second));
	ASSERT_TRUE(enumerator->next());
	string sName = enumerator->current().firstName;
	ASSERT_FALSE(enumerator->equals(second));
	ASSERT_EQ(fName, second->current().firstName);

	while (enumerator->next());

	ASSERT_EQ(fName, second->current().firstName);
	ASSERT_TRUE(second->next());
	ASSERT_EQ(sName, second->current().firstName);
}

TEST(XLinqFromMultiSetSharedPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsMultiSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->current();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromMultiSetSharedPtrTest, CallBackBeforeEnumerationWasStarted)
{
	auto persons = getPersonsMultiSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->back();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromMultiSetSharedPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsMultiSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->current();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromMultiSetSharedPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsMultiSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->next();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromMultiSetSharedPtrTest, BidirectionalEnumerableFromBegin)
{
	auto persons = getPersonsMultiSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	std::set<Person> occuredPersons;

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_FALSE(enumerator->next());
	ASSERT_EQ(6, occuredPersons.size());

	occuredPersons.clear();
	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_FALSE(enumerator->back());
	ASSERT_EQ(6, occuredPersons.size());
}

TEST(XLinqFromMultiSetSharedPtrTest, BidirectionalEnumerableFromEnd)
{
	auto persons = getPersonsMultiSetSharedPtr();
	auto enumerator = from(persons) >> getEndEnumerator();
	std::set<Person> occuredPersons;

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current());

	ASSERT_FALSE(enumerator->back());
	ASSERT_EQ(6, occuredPersons.size());

	occuredPersons.clear();
}

TEST(XLinqFromMultiSetSharedPtrTest, BidirectionalEnumerableEmpty)
{
	typedef std::multiset<int> tcontainer;
	std::shared_ptr<tcontainer> container(new tcontainer());
	ASSERT_FALSE((from(container) >> getEnumerator())->next());
	ASSERT_FALSE((from(container) >> getEndEnumerator())->back());
}

TEST(XLinqFromMultiSetSharedPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsMultiSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();

	ASSERT_TRUE(enumerator->next());
	string fName = enumerator->current().firstName;
	auto second = enumerator->clone();
	ASSERT_TRUE(enumerator->equals(second));
	ASSERT_TRUE(enumerator->next());
	string sName = enumerator->current().firstName;
	ASSERT_FALSE(enumerator->equals(second));
	ASSERT_EQ(fName, second->current().firstName);

	while (enumerator->next());

	ASSERT_EQ(fName, second->current().firstName);
	ASSERT_TRUE(second->next());
	ASSERT_EQ(sName, second->current().firstName);
}

TEST(XLinqFromMapSharedPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->current();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromMapSharedPtrTest, CallBackBeforeEnumerationWasStarted)
{
	auto persons = getPersonsMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->back();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromMapSharedPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->current();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromMapSharedPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->next();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromMapSharedPtrTest, BidirectionalEnumerableBegin)
{
	auto persons = getPersonsMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	std::set<Person> occuredPersons;

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_FALSE(enumerator->next());
	ASSERT_EQ(6, occuredPersons.size());

	occuredPersons.clear();
	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_FALSE(enumerator->back());
	ASSERT_EQ(6, occuredPersons.size());
}

TEST(XLinqFromMapSharedPtrTest, BidirectionalEnumerableEnd)
{
	auto persons = getPersonsMapSharedPtr();
	auto enumerator = from(persons) >> getEndEnumerator();
	std::set<Person> occuredPersons;

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_FALSE(enumerator->back());
	ASSERT_EQ(6, occuredPersons.size());

	occuredPersons.clear();
}

TEST(XLinqFromMapSharedPtrTest, BidirectionalEnumerableEmpty)
{
	typedef std::map<int, int> tcontainer;
	std::shared_ptr<tcontainer> container(new tcontainer());
	ASSERT_FALSE((from(container) >> getEnumerator())->next());
	ASSERT_FALSE((from(container) >> getEndEnumerator())->back());
}

TEST(XLinqFromMapSharedPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();

	ASSERT_TRUE(enumerator->next());
	string fName = enumerator->current().second.firstName;
	auto second = enumerator->clone();
	ASSERT_TRUE(enumerator->equals(second));
	ASSERT_TRUE(enumerator->next());
	string sName = enumerator->current().second.firstName;
	ASSERT_FALSE(enumerator->equals(second));
	ASSERT_EQ(fName, second->current().second.firstName);

	while (enumerator->next());

	ASSERT_EQ(fName, second->current().second.firstName);
	ASSERT_TRUE(second->next());
	ASSERT_EQ(sName, second->current().second.firstName);
}

TEST(XLinqFromMultiMapSharedPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsMultiMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->current().second;
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromMultiMapSharedPtrTest, CallBackBeforeEnumerationWasStarted)
{
	auto persons = getPersonsMultiMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->back();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromMultiMapSharedPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsMultiMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->current().second;
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromMultiMapSharedPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsMultiMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->next();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromMultiMapSharedPtrTest, BidirectionalEnumerableBegin)
{
	auto persons = getPersonsMultiMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	std::set<Person> occuredPersons;

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_FALSE(enumerator->next());
	ASSERT_EQ(6, occuredPersons.size());

	occuredPersons.clear();
	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_FALSE(enumerator->back());
	ASSERT_EQ(6, occuredPersons.size());
}

TEST(XLinqFromMultiMapSharedPtrTest, BidirectionalEnumerableEnd)
{
	auto persons = getPersonsMultiMapSharedPtr();
	auto enumerator = from(persons) >> getEndEnumerator();
	std::set<Person> occuredPersons;

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->back());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_FALSE(enumerator->back());
	ASSERT_EQ(6, occuredPersons.size());

	occuredPersons.clear();
}

TEST(XLinqFromMultiMapSharedPtrTest, BidirectionalEnumerableEmpty)
{
	typedef std::multimap<int, int> tcontainer;
	std::shared_ptr<tcontainer> container(new tcontainer());
	ASSERT_FALSE((from(container) >> getEnumerator())->next());
	ASSERT_FALSE((from(container) >> getEndEnumerator())->back());
}

TEST(XLinqFromMultiMapSharedPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsMultiMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();

	ASSERT_TRUE(enumerator->next());
	string fName = enumerator->current().second.firstName;
	auto second = enumerator->clone();
	ASSERT_TRUE(enumerator->equals(second));
	ASSERT_TRUE(enumerator->next());
	string sName = enumerator->current().second.firstName;
	ASSERT_FALSE(enumerator->equals(second));
	ASSERT_EQ(fName, second->current().second.firstName);

	while (enumerator->next());

	ASSERT_EQ(fName, second->current().second.firstName);
	ASSERT_TRUE(second->next());
	ASSERT_EQ(sName, second->current().second.firstName);
}

TEST(XLinqFromUnorderedSetSharedPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsUnorderedSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->current();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromUnorderedSetSharedPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->current();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromUnorderedSetSharedPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->next();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromUnorderedSetSharedPtrTest, EnumerableBegin)
{
	auto persons = getPersonsUnorderedSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	std::set<Person> occuredPersons;

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_FALSE(enumerator->next());
	ASSERT_EQ(6, occuredPersons.size());
}

TEST(XLinqFromUnorderedSetSharedPtrTest, EnumerableEmpty)
{
	typedef std::unordered_set<int> tcontainer;
	std::shared_ptr<tcontainer> container(new tcontainer());
	ASSERT_FALSE((from(container) >> getEnumerator())->next());
}

TEST(XLinqFromUnorderedSetSharedPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsUnorderedSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();

	ASSERT_TRUE(enumerator->next());
	string fName = enumerator->current().firstName;
	auto second = enumerator->clone();
	ASSERT_TRUE(enumerator->equals(second));
	ASSERT_TRUE(enumerator->next());
	string sName = enumerator->current().firstName;
	ASSERT_FALSE(enumerator->equals(second));
	ASSERT_EQ(fName, second->current().firstName);

	while (enumerator->next());

	ASSERT_EQ(fName, second->current().firstName);
	ASSERT_TRUE(second->next());
	ASSERT_EQ(sName, second->current().firstName);
}

TEST(XLinqFromUnorderedMultiSetSharedPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsUnorderedMultiSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->current();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromUnorderedMultiSetSharedPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedMultiSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->current();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromUnorderedMultiSetSharedPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedMultiSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->next();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromUnorderedMultiSetSharedPtrTest, EnumerableBegin)
{
	auto persons = getPersonsUnorderedMultiSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	std::set<Person> occuredPersons;

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current());

	ASSERT_FALSE(enumerator->next());
	ASSERT_EQ(6, occuredPersons.size());
}

TEST(XLinqFromUnorderedMultiSetSharedPtrTest, EnumerableEmpty)
{
	typedef std::unordered_multiset<int> tcontainer;
	std::shared_ptr<tcontainer> container(new tcontainer());
	ASSERT_FALSE((from(container) >> getEnumerator())->next());
}

TEST(XLinqFromUnorderedMultiSetSharedPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsUnorderedMultiSetSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();

	ASSERT_TRUE(enumerator->next());
	string fName = enumerator->current().firstName;
	auto second = enumerator->clone();
	ASSERT_TRUE(enumerator->equals(second));
	ASSERT_TRUE(enumerator->next());
	string sName = enumerator->current().firstName;
	ASSERT_FALSE(enumerator->equals(second));
	ASSERT_EQ(fName, second->current().firstName);

	while (enumerator->next());

	ASSERT_EQ(fName, second->current().firstName);
	ASSERT_TRUE(second->next());
	ASSERT_EQ(sName, second->current().firstName);
}

TEST(XLinqFromUnorderedMapSharedPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsUnorderedMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->current();
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromUnorderedMapSharedPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->current();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromUnorderedMapSharedPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->next();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromUnorderedMapSharedPtrTest, EnumerableBegin)
{
	auto persons = getPersonsUnorderedMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	std::set<Person> occuredPersons;

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_FALSE(enumerator->next());
	ASSERT_EQ(6, occuredPersons.size());
}

TEST(XLinqFromUnorderedMapSharedPtrTest, EnumerableEmpty)
{
	typedef std::unordered_map<int, int> tcontainer;
	std::shared_ptr<tcontainer> container(new tcontainer());
	ASSERT_FALSE((from(container) >> getEnumerator())->next());
}

TEST(XLinqFromUnorderedMapSharedPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsUnorderedMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();

	ASSERT_TRUE(enumerator->next());
	string fName = enumerator->current().second.firstName;
	auto second = enumerator->clone();
	ASSERT_TRUE(enumerator->equals(second));
	ASSERT_TRUE(enumerator->next());
	string sName = enumerator->current().second.firstName;
	ASSERT_FALSE(enumerator->equals(second));
	ASSERT_EQ(fName, second->current().second.firstName);

	while (enumerator->next());

	ASSERT_EQ(fName, second->current().second.firstName);
	ASSERT_TRUE(second->next());
	ASSERT_EQ(sName, second->current().second.firstName);
}

TEST(XLinqFromUnorderedMultiMapSharedPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsUnorderedMultiMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	try
	{
		enumerator->current().second;
	}
	catch (IterationNotStartedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromUnorderedMultiMapSharedPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedMultiMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->current().second;
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromUnorderedMultiMapSharedPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedMultiMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	while (enumerator->next());
	try
	{
		enumerator->next();
	}
	catch (IterationFinishedException)
	{
		return;
	}
	catch (...)
	{
		FAIL();
	}
	FAIL();
}

TEST(XLinqFromUnorderedMultiMapSharedPtrTest, EnumerableBegin)
{
	auto persons = getPersonsUnorderedMultiMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();
	std::set<Person> occuredPersons;

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_TRUE(enumerator->next());
	occuredPersons.insert(enumerator->current().second);

	ASSERT_FALSE(enumerator->next());
	ASSERT_EQ(6, occuredPersons.size());
}

TEST(XLinqFromUnorderedMultiMapSharedPtrTest, EnumerableEmpty)
{
	typedef std::unordered_multimap<int, int> tcontainer;
	std::shared_ptr<tcontainer> container(new tcontainer());
	ASSERT_FALSE((from(container) >> getEnumerator())->next());
}

TEST(XLinqFromUnorderedMultiMapSharedPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsUnorderedMultiMapSharedPtr();
	auto enumerator = from(persons) >> getEnumerator();

	ASSERT_TRUE(enumerator->next());
	string fName = enumerator->current().second.firstName;
	auto second = enumerator->clone();
	ASSERT_TRUE(enumerator->equals(second));
	ASSERT_TRUE(enumerator->next());
	string sName = enumerator->current().second.firstName;
	ASSERT_FALSE(enumerator->equals(second));
	ASSERT_EQ(fName, second->current().second.firstName);

	while (enumerator->next());

	ASSERT_EQ(fName, second->current().second.firstName);
	ASSERT_TRUE(second->next());
	ASSERT_EQ(sName, second->current().second.firstName);
}
