#ifndef SEARCH_HPP
#define SEARCH_HPP

class Search
{
public:
    // TODO - fix virutal destructors
//    virtual ~Search();
    virtual void start() = 0;
    virtual int step() = 0;
};

#endif // SEARCH_HPP
