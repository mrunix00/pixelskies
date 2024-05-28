#pragma once

#include "utils.h"
#include <optional>
#include <string>
#include <vector>

struct BlueskyError {
    std::string code{};
    std::string message{};
};

struct BlueskyVerificationMethod {
    std::string id;
    std::string type;
    std::string controller;
    std::string publicKeyMultibase;
};

struct BlueskyService {
    std::string id;
    std::string type;
    std::string serviceEndpoint;
};

struct DidDoc {
    std::vector<std::string> context;
    std::string id;
    std::vector<std::string> knownAs;
    std::vector<BlueskyVerificationMethod> verificationMethods;
    std::vector<BlueskyService> services;
};

struct BlueskyProfile {
    std::string did;
    std::string handle;
    std::string displayName;
    std::string avatar;
    u_int64_t followersCount;
    u_int64_t followsCount;
    u_int64_t postsCount;
};

struct BlueskySession {
    std::string did;
    DidDoc didDoc;
    std::string handle;
    std::string email;
    bool emailConfirmed;
    bool emailAuthFactor;
    std::string accessJWT;
    std::string refreshJWT;
    std::string provider;
};

class Bluesky {
public:
    BlueskySession session{};

    Bluesky();

    ~Bluesky();

    std::optional<BlueskyError> signIn(
            const std::string &provider,
            const std::string &identifier,
            const std::string &password);

    std::optional<BlueskyError> signUp(
            const std::string &provider,
            const std::string &identifier,
            const std::string &password);

    [[nodiscard]] Either<BlueskyError, BlueskyProfile> getProfile() const;
};