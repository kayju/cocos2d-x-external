cmake_minimum_required(VERSION 3.6)
project(Box2D)

set(BOX2D_SRC
    Box2D/Collision/b2BroadPhase.cpp
    Box2D/Collision/b2CollideCircle.cpp
    Box2D/Collision/b2CollideEdge.cpp
    Box2D/Collision/b2CollidePolygon.cpp
    Box2D/Collision/b2Collision.cpp
    Box2D/Collision/b2Distance.cpp
    Box2D/Collision/b2DynamicTree.cpp
    Box2D/Collision/b2TimeOfImpact.cpp
    Box2D/Collision/Shapes/b2ChainShape.cpp
    Box2D/Collision/Shapes/b2CircleShape.cpp
    Box2D/Collision/Shapes/b2EdgeShape.cpp
    Box2D/Collision/Shapes/b2PolygonShape.cpp
    Box2D/Common/b2BlockAllocator.cpp
    Box2D/Common/b2Draw.cpp
    Box2D/Common/b2Math.cpp
    Box2D/Common/b2Settings.cpp
    Box2D/Common/b2StackAllocator.cpp
    Box2D/Common/b2Timer.cpp
    Box2D/Dynamics/b2Body.cpp
    Box2D/Dynamics/b2ContactManager.cpp
    Box2D/Dynamics/b2Fixture.cpp
    Box2D/Dynamics/b2Island.cpp
    Box2D/Dynamics/b2World.cpp
    Box2D/Dynamics/b2WorldCallbacks.cpp
    Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
    Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
    Box2D/Dynamics/Contacts/b2CircleContact.cpp
    Box2D/Dynamics/Contacts/b2Contact.cpp
    Box2D/Dynamics/Contacts/b2ContactSolver.cpp
    Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
    Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
    Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
    Box2D/Dynamics/Contacts/b2PolygonContact.cpp
    Box2D/Dynamics/Joints/b2DistanceJoint.cpp
    Box2D/Dynamics/Joints/b2FrictionJoint.cpp
    Box2D/Dynamics/Joints/b2GearJoint.cpp
    Box2D/Dynamics/Joints/b2Joint.cpp
    Box2D/Dynamics/Joints/b2MotorJoint.cpp
    Box2D/Dynamics/Joints/b2MouseJoint.cpp
    Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
    Box2D/Dynamics/Joints/b2PulleyJoint.cpp
    Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
    Box2D/Dynamics/Joints/b2RopeJoint.cpp
    Box2D/Dynamics/Joints/b2WeldJoint.cpp
    Box2D/Dynamics/Joints/b2WheelJoint.cpp
    Box2D/Rope/b2Rope.cpp
)

add_library(Box2D STATIC
    ${BOX2D_SRC}
)

# TODO: check why target_compile_features does work for IOS
if (NOT IOS)
    target_compile_features(Box2D PUBLIC cxx_nullptr)
endif()

target_include_directories(Box2D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
