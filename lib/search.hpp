#pragma once

class Search
{
public:
    virtual ~Search() {}
    virtual void start() = 0;
    virtual void step() = 0;
};
