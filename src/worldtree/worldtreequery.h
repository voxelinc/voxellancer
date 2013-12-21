#pragma once


template<typename Shape>
class WorldTreeQuery {
    WorldTreeQuery(WorldTree* worldTree);

    void setNodeHint(WorldTreeNode* nodeHint);
    void setCollidableWith(WorldObject* worldObject)


    bool areGeodesIntersecting() const;
    std::set<WorldTreeGeode*> intersectingGeodes() const;

    bool areVoxelsIntersecting() const;
    std::set<Voxel*> intersectingVoxels() const;

    bool areWorldObjectsIntersecting() const;
    std::set<Voxel*> intersectingVoxels() const;
};
