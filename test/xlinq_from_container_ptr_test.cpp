#include <gtest/gtest.h>
#include "model/xlinq_test_model.h"
#include <xlinq/xlinq_from_container_ptr.h>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;
using namespace xlinq;

TEST(XLinqFromVectorPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersons();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromVectorPtrTest, CallBackBeforeEnumerationWasStarted)
{
	auto persons = getPersons();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromVectorPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersons();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromVectorPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersons();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromVectorPtrTest, RandomAccessEnumerableBegin)
{
	auto persons = getPersons();
	auto enumerator = from(&persons) >> getEnumerator();

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

TEST(XLinqFromVectorPtrTest, RandomAccessEnumerableEnd)
{
	auto persons = getPersons();
	auto enumerator = from(&persons) >> getEndEnumerator();

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

TEST(XLinqFromVectorPtrTest, RandomAccessEnumerableAt)
{
	auto persons = getPersons();
	auto enumerator = from(&persons) >> getEnumeratorAt(2);

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

TEST(XLinqFromVectorPtrTest, RandomAccessEnumerableEmpty)
{
	std::vector<int> container;
	ASSERT_FALSE((from(&container) >> getEnumerator())->next());
	ASSERT_FALSE((from(&container) >> getEndEnumerator())->back());
	ASSERT_FALSE((from(&container) >> getEnumerator())->advance(1));
	ASSERT_FALSE((from(&container) >> getEnumerator())->advance(-1));
}

TEST(XLinqFromVectorPtrTest, RandomAccessEnumerableSize)
{
	auto persons = getPersons();
	ASSERT_EQ(6, from(&persons)->size());
}

TEST(XLinqFromVectorPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersons();
	auto enumerator = from(&persons) >> getEnumerator();

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

TEST(XLinqFromVectorPtrTest, DistanceLtGtTest)
{
	auto persons = getPersons();
	auto enumerable = from(&persons);
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

TEST(XLinqFromListPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsList();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromListPtrTest, CallBackBeforeEnumerationWasStarted)
{
	auto persons = getPersonsList();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromListPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsList();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromListPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsList();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromListPtrTest, BidirectionalEnumerableBegin)
{
	auto persons = getPersonsList();
	auto enumerator = from(&persons) >> getEnumerator();

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

TEST(XLinqFromListPtrTest, BidirectionalEnumerableEnd)
{
	auto persons = getPersonsList();
	auto enumerator = from(&persons) >> getEndEnumerator();

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

TEST(XLinqFromListPtrTest, BidirectionalEnumerableEmpty)
{
	std::list<int> container;
	ASSERT_FALSE((from(&container) >> getEnumerator())->next());
	ASSERT_FALSE((from(&container) >> getEndEnumerator())->back());
}

TEST(XLinqFromListPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsList();
	auto enumerator = from(&persons) >> getEnumerator();

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

TEST(XLinqFromForwardListPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsForwardList();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromForwardListPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsForwardList();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromForwardListPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsForwardList();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromForwardListPtrTest, EnumerableBegin)
{
	auto persons = getPersonsForwardList();
	auto enumerator = from(&persons) >> getEnumerator();

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

TEST(XLinqFromForwardListPtrTest, EnumerableEmpty)
{
	std::forward_list<int> container;
	ASSERT_FALSE((from(&container) >> getEnumerator())->next());
}

TEST(XLinqFromForwardListPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsForwardList();
	auto enumerator = from(&persons) >> getEnumerator();

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

TEST(XLinqFromSetPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromSetPtrTest, CallBackBeforeEnumerationWasStarted)
{
	auto persons = getPersonsSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromSetPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromSetPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromSetPtrTest, BidirectionalEnumerableBegin)
{
	auto persons = getPersonsSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromSetPtrTest, BidirectionalEnumerableEnd)
{
	auto persons = getPersonsSet();
	auto enumerator = from(&persons) >> getEndEnumerator();
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

TEST(XLinqFromSetPtrTest, BidirectionalEnumerableEmpty)
{
	std::set<int> container;
	ASSERT_FALSE((from(&container) >> getEnumerator())->next());
	ASSERT_FALSE((from(&container) >> getEndEnumerator())->back());
}

TEST(XLinqFromSetPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsSet();
	auto enumerator = from(&persons) >> getEnumerator();

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

TEST(XLinqFromMultiSetPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsMultiSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMultiSetPtrTest, CallBackBeforeEnumerationWasStarted)
{
	auto persons = getPersonsMultiSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMultiSetPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsMultiSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMultiSetPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsMultiSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMultiSetPtrTest, BidirectionalEnumerableFromBegin)
{
	auto persons = getPersonsMultiSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMultiSetPtrTest, BidirectionalEnumerableFromEnd)
{
	auto persons = getPersonsMultiSet();
	auto enumerator = from(&persons) >> getEndEnumerator();
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

TEST(XLinqFromMultiSetPtrTest, BidirectionalEnumerableEmpty)
{
	std::multiset<int> container;
	ASSERT_FALSE((from(&container) >> getEnumerator())->next());
	ASSERT_FALSE((from(&container) >> getEndEnumerator())->back());
}

TEST(XLinqFromMultiSetPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsMultiSet();
	auto enumerator = from(&persons) >> getEnumerator();

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

TEST(XLinqFromMapPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMapPtrTest, CallBackBeforeEnumerationWasStarted)
{
	auto persons = getPersonsMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMapPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMapPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMapPtrTest, BidirectionalEnumerableBegin)
{
	auto persons = getPersonsMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMapPtrTest, BidirectionalEnumerableEnd)
{
	auto persons = getPersonsMap();
	auto enumerator = from(&persons) >> getEndEnumerator();
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

TEST(XLinqFromMapPtrTest, BidirectionalEnumerableEmpty)
{
	std::map<int, int> container;
	ASSERT_FALSE((from(&container) >> getEnumerator())->next());
	ASSERT_FALSE((from(&container) >> getEndEnumerator())->back());
}

TEST(XLinqFromMapPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsMap();
	auto enumerator = from(&persons) >> getEnumerator();

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

TEST(XLinqFromMultiMapPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsMultiMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMultiMapPtrTest, CallBackBeforeEnumerationWasStarted)
{
	auto persons = getPersonsMultiMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMultiMapPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsMultiMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMultiMapPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsMultiMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMultiMapPtrTest, BidirectionalEnumerableBegin)
{
	auto persons = getPersonsMultiMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromMultiMapPtrTest, BidirectionalEnumerableEnd)
{
	auto persons = getPersonsMultiMap();
	auto enumerator = from(&persons) >> getEndEnumerator();
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

TEST(XLinqFromMultiMapPtrTest, BidirectionalEnumerableEmpty)
{
	std::multimap<int, int> container;
	ASSERT_FALSE((from(&container) >> getEnumerator())->next());
	ASSERT_FALSE((from(&container) >> getEndEnumerator())->back());
}

TEST(XLinqFromMultiMapPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsMultiMap();
	auto enumerator = from(&persons) >> getEnumerator();

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

TEST(XLinqFromUnorderedSetPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsUnorderedSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedSetPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedSetPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedSetPtrTest, EnumerableBegin)
{
	auto persons = getPersonsUnorderedSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedSetPtrTest, EnumerableEmpty)
{
	std::unordered_set<int> container;
	ASSERT_FALSE((from(&container) >> getEnumerator())->next());
}

TEST(XLinqFromUnorderedSetPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsUnorderedSet();
	auto enumerator = from(&persons) >> getEnumerator();

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

TEST(XLinqFromUnorderedMultiSetPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsUnorderedMultiSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedMultiSetPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedMultiSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedMultiSetPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedMultiSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedMultiSetPtrTest, EnumerableBegin)
{
	auto persons = getPersonsUnorderedMultiSet();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedMultiSetPtrTest, EnumerableEmpty)
{
	std::unordered_multiset<int> container;
	ASSERT_FALSE((from(&container) >> getEnumerator())->next());
}

TEST(XLinqFromUnorderedMultiSetPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsUnorderedMultiSet();
	auto enumerator = from(&persons) >> getEnumerator();

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

TEST(XLinqFromUnorderedMapPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsUnorderedMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedMapPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedMapPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedMapPtrTest, EnumerableBegin)
{
	auto persons = getPersonsUnorderedMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedMapPtrTest, EnumerableEmpty)
{
	std::unordered_map<int, int> container;
	ASSERT_FALSE((from(&container) >> getEnumerator())->next());
}

TEST(XLinqFromUnorderedMapPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsUnorderedMap();
	auto enumerator = from(&persons) >> getEnumerator();

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

TEST(XLinqFromUnorderedMultiMapPtrTest, CallCurrentBeforeEnumerationWasStarted)
{
	auto persons = getPersonsUnorderedMultiMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedMultiMapPtrTest, CallCurrentWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedMultiMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedMultiMapPtrTest, CallNextWhenEnumerationWasFinished)
{
	auto persons = getPersonsUnorderedMultiMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedMultiMapPtrTest, EnumerableBegin)
{
	auto persons = getPersonsUnorderedMultiMap();
	auto enumerator = from(&persons) >> getEnumerator();
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

TEST(XLinqFromUnorderedMultiMapPtrTest, EnumerableEmpty)
{
	std::unordered_multimap<int, int> container;
	ASSERT_FALSE((from(&container) >> getEnumerator())->next());
}

TEST(XLinqFromUnorderedMultiMapPtrTest, CloneAndEqualsEnumeratorTest)
{
	auto persons = getPersonsUnorderedMultiMap();
	auto enumerator = from(&persons) >> getEnumerator();

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
