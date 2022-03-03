//
// Created by alexm on 1/03/2022.
//

#ifndef SLIMEMATHS_TRANSFORM_H
#define SLIMEMATHS_TRANSFORM_H

#include "Mat4.h"
#include "Quaternion.h"

// Create these functions
//https://docs.unity3d.com/ScriptReference/Transform.html

struct Transform : public Mat4 {
//Properties
    std::string name;                                       //Name of Transform.
    int childCount;                                         //The number of children the parent Transform has.
    Vec3 eulerAngles;                                       //The rotation as Euler angles in degrees.
    Vec3 forward;                                           //Returns a normalized vector representing the blue axis of the transform in world space.
    bool hasChanged;                                        //Has the transform changed since the last time the flag was set to 'false'?
    int hierarchyCapacity;                                  //The transform capacity of the transform's hierarchy data structure.
    int hierarchyCount;                                     //The number of transforms in the transform's hierarchy data structure.
    Vec3 localEulerAngles;                                  //The rotation as Euler angles in degrees relative to the parent transform's rotation.
    Vec3 localPosition;                                     //Position of the transform relative to the parent transform.
    Quaternion localRotation;                               //The rotation of the transform relative to the transform rotation of the parent.
    Vec3 localScale;                                        //The scale of the transform relative to the GameObjects parent.
    Mat4 localToWorldMatrix;                                //Matrix that transforms a point from local space into world space (Read Only).
    Vec3 lossyScale;                                        //The global scale of the object (Read Only).
    Transform *parent;                                      //The parent of the transform.
    Vec3 position;                                          //The world space position of the Transform.
    Vec3 right;                                             //The red axis of the transform in world space.
    Transform *root;                                        //Returns the topmost transform in the hierarchy.
    Quaternion rotation;                                    //A Quaternion that stores the rotation of the Transform in world space.
    Vec3 up;                                                //The green axis of the transform in world space.
    Mat4 worldToLocalMatrix;                                //Matrix that transforms a point from world space into local space (Read Only).

//Methods
    void DetachChildren();                                  //Un-parents all children.
    Transform *Find(std::string name);                      //Finds a child by n and returns it.
    Transform *GetChild(int index);                         //Returns a transform child by index.
    int GetSiblingIndex();                                  //Gets the sibling index.
    Vec3 InverseTransformDirection(
            Vec3 direction);                                //Transforms a direction from world space to local space. The opposite of Transform.TransformDirection.
    Vec3 InverseTransformPoint(Vec3 position);              //Transforms position from world space to local space.
    Vec3 InverseTransformVector(
            Vec3 vector);                                   //Transforms a vector from world space to local space. The opposite of Transform.TransformVector.
    bool IsChildOf(Transform parent);                       //Is this transform a child of parent?
    void
    LookAt(Transform target);                               //Rotates the transform so the forward vector points at /target/'s current position.
    void
    Rotate(Vec3 eulers);                                    //Use Transform.Rotate to rotate GameObjects in a variety of ways. The rotation is often provided as an Euler angle and not a Quaternion.
    void RotateAround(Vec3 point, Vec3 axis,
                      float angle);                         //Rotates the transform about axis passing through point in world coordinates by angle degrees.
    void SetAsFirstSibling();                               //Move the transform to the start of the local transform list.
    void SetAsLastSibling();                                //Move the transform to the end of the local transform list.
    void SetParent(Transform *parent);                      //Set the parent of the transform.
    void SetPositionAndRotation(Vec3 position,
                                Quaternion rotation);       //Sets the world space position and rotation of the Transform component.
    void SetSiblingIndex(int index);                        //Sets the sibling index.
    Vec3 TransformDirection(Vec3 direction);                //Transforms direction from local space to world space.
    Vec3 TransformPoint(Vec3 position);                     //Transforms position from local space to world space.
    Vec3 TransformVector(Vec3 vector);                      //Transforms vector from local space to world space.
    void Translate(Vec3 translation);                       //Moves the transform in the direction and distance of translation.
};


#endif //SLIMEMATHS_TRANSFORM_H
