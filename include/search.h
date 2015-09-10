#ifndef SEARCH_H
#define SEARCH_H

class Search
{
public:
    virtual ~Search() {}
    virtual void start() = 0;
    virtual void step() = 0;
};

#endif /* SEARCH_H */
