#ifndef SEARCH_HPP
#define SEARCH_HPP

class Search
{
public:
    virtual ~Search() {}
    virtual void start() = 0;
    virtual void step() = 0;
};

#endif // SEARCH_HPP
