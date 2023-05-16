#pragma once
#include "STL_storage.h"
#include <iostream>
#include <vector>
#include <cmath>

class ObjectNode {
public:
    int id;
    float left, right, top, bottom;

    ObjectNode(int id, float left, float right, float top, float bottom) {
        this->id = id;
        this->left = left;
        this->right = right;
        this->top = top;
        this->bottom = bottom;
    }
};

class TreeNode {
public:
    float left, right, top, bottom;
    vector<ObjectNode*> objects;
    TreeNode* nw = nullptr;
    TreeNode* ne = nullptr;
    TreeNode* sw = nullptr;
    TreeNode* se = nullptr;

    TreeNode(float left, float right, float top, float bottom) {
        this->left = left;
        this->right = right;
        this->top = top;
        this->bottom = bottom;
    }

    ~TreeNode() {
        for (auto& object : objects) {
            delete object;
        }
        if (nw) delete nw;
        if (ne) delete ne;
        if (sw) delete sw;
        if (se) delete se;
    }

    bool contains(ObjectNode* object) {
        return (object->left >= left && object->right <= right && object->top >= top && object->bottom <= bottom);
    }

    bool intersects(float x, float y, float radius) {
        float closestX = max(left, min(x, right));
        float closestY = max(bottom, min(y, top));
        float distanceX = x - closestX;
        float distanceY = y - closestY;
        float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
        return distanceSquared < (radius * radius);
    }

    void insert(ObjectNode* object, int maxLevel, int currentLevel = 0) {
        if (!contains(object)) {
            return;
        }
        if (objects.size() < 4 || currentLevel >= maxLevel) {
            objects.push_back(object);
            return;
        }
        if (!nw) nw = new TreeNode(left, (left + right) / 2.0f, top, (top + bottom) / 2.0f);
        if (!ne) ne = new TreeNode((left + right) / 2.0f, right, top, (top + bottom) / 2.0f);
        if (!sw) sw = new TreeNode(left, (left + right) / 2.0f, (top + bottom) / 2.0f, bottom);
        if (!se) se = new TreeNode((left + right) / 2.0f, right, (top + bottom) / 2.0f, bottom);
        nw->insert(object, maxLevel, currentLevel + 1);
        ne->insert(object, maxLevel, currentLevel + 1);
        sw->insert(object, maxLevel, currentLevel + 1);
        se->insert(object, maxLevel, currentLevel + 1);
    }

    void remove(int objectId) {
        for (auto it = objects.begin(); it != objects.end(); it++) {
            if ((*it)->id == objectId) {
                delete (*it);
                objects.erase(it);
                return;
            }
        }
        if (nw) nw->remove(objectId);
        if (ne) ne->remove(objectId);
        if (sw) sw->remove(objectId);
        if (se) se->remove(objectId);
    }

    void update(int objectId, float newLeft, float newRight, float newTop, float newBottom) {
        for (auto& object : objects) {
            if (object->id == objectId) {
                object->left = newLeft;
                object->right = newRight;
                object->top = newTop;
                object->bottom = newBottom;
                return;
            }
        }
        if (nw) nw->update(objectId, newLeft, newRight, newTop, newBottom);
        if (ne) ne->update(objectId, newLeft, newRight, newTop, newBottom);
        if (sw) sw->update(objectId, newLeft, newRight, newTop, newBottom);
        if (se) se->update(objectId, newLeft, newRight, newTop, newBottom);
    }

    void getObjectsNear(float x, float y, float radius, vector<ObjectNode*>& nearbyObjects) {
        if (!intersects(x, y, radius)) {
            return;
        }   
        for (auto& object : objects) {
            float centerX = (object->left + object->right) / 2.0f;
            float centerY = (object->top + object->bottom) / 2.0f;
            if (intersects(centerX, centerY, radius)) {
                nearbyObjects.push_back(object);
            }
        }
        if (nw) nw->getObjectsNear(x, y, radius, nearbyObjects);
        if (ne) ne->getObjectsNear(x, y, radius, nearbyObjects);
        if (sw) sw->getObjectsNear(x, y, radius, nearbyObjects);
        if (se) se->getObjectsNear(x, y, radius, nearbyObjects);
    }
};

class Quadtree {
public:
    TreeNode* root;

    Quadtree(float left, float right, float top, float bottom) {
        root = new TreeNode(left, right, top, bottom);
    }

    ~Quadtree() {
        delete root;
    }

    void insert(int objectId, float left, float right, float top, float bottom, int maxLevel) {
        auto object = new ObjectNode(objectId, left, right, top, bottom);
        root->insert(object, maxLevel);
    }

    void remove(int objectId) {
        root->remove(objectId);
    }

    void update(int objectId, float newLeft, float newRight, float newTop, float newBottom) {
        root->update(objectId, newLeft, newRight, newTop, newBottom);
    }

    vector<ObjectNode*> getObjectsNear(float x, float y, float radius) {
        vector<ObjectNode*> nearbyObjects;
        root->getObjectsNear(x, y, radius, nearbyObjects);
        return nearbyObjects;
    }
};

