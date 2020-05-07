

#ifndef _PATH_
#define _PATH_

class Path{
private:
    *city_node m_path;
public:
    Path(const int stops)
        {
            m_path = new city_node[stops];
        }
    void printPath() const
    {
        if(m_path == NULL)
            return;
        for(int i=0; i<sizeof(m_path[0])/sizeof(m_path); i++)
            std::cout << m_path[i].getName() << std::endl;
    }
};

#endif