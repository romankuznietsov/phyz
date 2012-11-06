#ifndef ATOMLIST_H
#define ATOMLIST_H


#include <vector>
#include <list>
#include <utility>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "Atom.h"


typedef std::pair<unsigned int, unsigned int> UIPair;
typedef std::list<UIPair> PairList;
typedef std::vector<PairList> PairLists;
typedef std::list<boost::thread*> Threads;


class Atoms : public std::vector<AtomPtr>
{
	private:
		PairLists _lists;
	public:
		Atoms();
		void update(float dt);
		void draw();
		void refresh();
};


typedef boost::shared_ptr<Atoms> AtomsPtr;


#endif // ATOMLIST_H
