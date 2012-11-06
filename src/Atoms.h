#ifndef ATOMLIST_H
#define ATOMLIST_H


#include <vector>
#include <list>
#include <utility>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "Atom.h"


typedef std::pair<unsigned int, unsigned int> AtomPair;
typedef std::list<AtomPair> AtomPairList;
typedef std::vector<AtomPairList> AtomPairLists;
typedef std::list<boost::thread*> Threads;


class Atoms : public std::vector<AtomPtr>
{
	private:
		AtomPairLists _lists;
		Threads _threads;
	public:
		Atoms();
		~Atoms();
		void update(float dt);
		void draw();
		void refresh();
};


typedef boost::shared_ptr<Atoms> AtomsPtr;


#endif // ATOMLIST_H
