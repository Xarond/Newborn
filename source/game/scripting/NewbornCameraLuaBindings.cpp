#include "NewbornCameraLuaBindings.hpp"
#include "NewbornLuaConverters.hpp"
#include "NewbornWorldCamera.hpp"
#include "NewbornRoot.hpp"

namespace Newborn {

LuaCallbacks LuaBindings::makeCameraCallbacks(WorldCamera* camera) {
    LuaCallbacks callbacks;

    callbacks.registerCallbackWithSignature<Vec2F>("position", bind(&WorldCamera::centerWorldPosition, camera));
    callbacks.registerCallbackWithSignature<float>("pixelRatio", bind(&WorldCamera::pixelRatio, camera));
    callbacks.registerCallback("setPixelRatio", [camera](float pixelRatio, Maybe<bool> smooth) {
        if (smooth.value())
            camera->setTargetPixelRatio(pixelRatio);
        else
            camera->setPixelRatio(pixelRatio);
        Root::singleton().configuration()->set("zoomLevel", pixelRatio);
    });

    callbacks.registerCallbackWithSignature<Vec2U>("screenSize", bind(&WorldCamera::screenSize, camera));
    callbacks.registerCallbackWithSignature<RectF>("worldScreenRect", bind(&WorldCamera::worldScreenRect, camera));
    callbacks.registerCallbackWithSignature<RectI>("worldTitleRect", bind(&WorldCamera::worldTileRect, camera));
    callbacks.registerCallbackWithSignature<Vec2F>("tileMinScreen", bind(&WorldCamera::tileMinScreen, camera));
    callbacks.registerCallbackWithSignature<Vec2F, Vec2F>("screenToWorld", bind(&WorldCamera::screenToWorld, camera, _1));
    callbacks.registerCallbackWithSignature<Vec2F, Vec2F>("worldToScreen", bind(&WorldCamera::worldToScreen, camera, _1));

    return callbacks;
}

}