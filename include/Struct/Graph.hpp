#pragma once

#include <iostream>

template <typename T>
class Graph {
private:
    T m_Data;
    Graph<T>[] *m_Neighbors;
    int m_NeighborCount;
    int m_MaxNeighbors;

public:
    /**
     * Constructor for the Graph class.
     * @ensure NeighborCount = 0
     * @ensure MaxNeighbors = 0
     */
    Graph(void) {
        this->m_NeighborCount = 0;
        this->m_MaxNeighbors = 0;
    }

    /**
     * Constructor for the Graph class.
     * @param maxNeighbors The maximum number of neighbors that can be stored.
     * @ensure NeighborCount = 0
     * @ensure MaxNeighbors = maxNeighbors
     */
    Graph(int maxNeighbors) {
        this->m_NeighborCount = 0;
        this->m_MaxNeighbors = maxNeighbors;
        this->m_Neighbors = new Graph<T>[maxNeighbors];
    }

    /**
     * Constructor for the Graph class.
     * @param graph The graph to copy.
     * @ensure NeighborCount = graph.NeighborCount
     * @ensure MaxNeighbors = graph.MaxNeighbors
     * @ensure Neighbors = graph.Neighbors
     * @ensure Data = graph.Data
     */
    Graph(Graph<T> *graph) {
        this->m_NeighborCount = graph->m_NeighborCount;
        this->m_MaxNeighbors = graph->m_MaxNeighbors;
        this->m_Neighbors = new Graph<T>[this->m_MaxNeighbors];
        for (int i = 0; i < this->m_NeighborCount; i++) {
            this->m_Neighbors[i] = graph->m_Neighbors[i];
        }
    }

    /**
     * Destructor for the Graph class.
     */
    ~Graph(void) {
        delete[] this->m_Neighbors;
    }

    /**
     * Add a neighbor to the graph.
     * @param neighbor The neighbor to add.
     * @ensure NeighborCount = NeighborCount + 1
     */
    void AddNeighbor(Graph<T> neighbor) {
        if (this->m_NeighborCount < this->m_MaxNeighbors) {
            this->m_Neighbors[this->m_NeighborCount] = neighbor;
            this->m_NeighborCount++;
        }
    }

    /**
     * Remove a neighbor from the graph.
     * @param neighbor The neighbor to remove.
     * @ensure NeighborCount = NeighborCount - 1
     */
    void RemoveNeighbor(Graph<T> neighbor) {
        for (int i = 0; i < this->m_NeighborCount; i++) {
            if (this->m_Neighbors[i] == neighbor) {
                this->m_Neighbors[i] = this->m_Neighbors[this->m_NeighborCount - 1];
                this->m_NeighborCount--;
                break;
            }
        }
    }

    /**
     * Set the data of the graph.
     * @param maxNeighbors The maximum number of neighbors that can be stored.
     * @esnure MaxNeighbors = maxNeighbors
     */
    void setMaxNeighbors(int maxNeighbors) {
        this->m_MaxNeighbors = maxNeighbors;
        this->m_Neighbors = new Graph<T>[maxNeighbors];
    }

    /**
     *
     * @param index
     */
    void RemoveNeighbor(int index) {
        if (index < this->m_NeighborCount) {
            this->m_Neighbors[index] = this->m_Neighbors[this->m_NeighborCount - 1];
            this->m_NeighborCount--;
        }
    }

    Graph<T> GetNeighbor(int index) {
        if (index < this->m_NeighborCount) {
            return this->m_Neighbors[index];
        }
        return Graph<T>();
    }

    int GetNeighborCount(void) {
        return this->m_NeighborCount;
    }

    T GetData(void) {
        return this->m_Data;
    }

    void SetData(T data) {
        this->m_Data = data;
    }

    void Print(void) {
        std::cout << this->m_Data << ": ";
        for (int i = 0; i < this->m_NeighborCount; i++) {
            std::cout << this->m_Neighbors[i].GetData() << " ";
        }
        std::cout << std::endl;
    }
};