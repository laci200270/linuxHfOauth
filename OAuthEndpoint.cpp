#include "OAuthEndpoint.h"
#include "fmt/format.h"

OAuthEndpoint::OAuthEndpoint(LoginValidation::LoginValidator &loginValidator, std::vector<spdlog::sink_ptr> logSinks)
        : loginValidator(loginValidator), logSinks(logSinks), logger(("OAuthEndpoint")) {
    logger.sinks().insert(logger.sinks().end(), logSinks.begin(), logSinks.end());
}


void OAuthEndpoint::authorizeCallback(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

    if (request.query().has("response_type") && request.query().has("client_id") &&
        request.query().has("redirect_uri") && request.query().has("scope") && request.query().has("state")) {
        auto responseType = *request.query().get("response_type");
        auto client_id = *request.query().get("client_id");
        auto redirect_uri = *request.query().get("redirect_uri");
        auto scope = *request.query().get("scope");
        auto state = *request.query().get("state");

        if (responseType == "code") {
            if (request.query().has("code_challenge") || request.query().has("code_challenge_method")) {
                response.send(Pistache::Http::Code::Not_Implemented);
                return;
            }
            std::string locationUri = "/";
            switch (request.method()) {
                case Pistache::Http::Method::Get:
                    locationUri = fmt::format(
                            "/authenticate?response_type={}&client_id={}&redirect_uri={}&scope={}&state={}",
                            responseType, client_id, redirect_uri, scope, state);
                    break;
                case Pistache::Http::Method::Post:

                    locationUri = urlDecode(redirect_uri);
                    break;
            }
            response.headers().add<Pistache::Http::Header::Location>(locationUri);
            response.send(Pistache::Http::Code::Found);
        } else {
            response.send(Pistache::Http::Code::Not_Implemented);
            return;
        }
    } else {
        response.send(Pistache::Http::Code::Bad_Request);
        return;
    }


    logger.flush();
}

void OAuthEndpoint::tokenCallback(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

}

void
OAuthEndpoint::authenticateCallback(const Pistache::Rest::Request &request,
                                    Pistache::Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>("text/html");
    response.send(Pistache::Http::Code::Ok, fmt::format(R"( <form method="POST" action="/authorize{0}">
                                                                                <label for="uname">Username:</label>
                                                                                <input type="text" id="uname" name="uname"><br><br>
                                                                                <label for="pw">Password:</label>
                                                                                <input type="password" id="pw" name="pw"><br><br>
                                                                                <input type="submit" value="Submit">
                                                                            </form>)", request.query().as_str()));;

}


std::string OAuthEndpoint::urlDecode(std::string source) {
    std::string returnable;
    char a, b;
    char *src = source.data();
    while (*src) {
        if ((*src == '%') &&
            ((a = src[1]) && (b = src[2])) &&
            (isxdigit(a) && isxdigit(b))) {
            if (a >= 'a')
                a -= 'a' - 'A';
            if (a >= 'A')
                a -= ('A' - 10);
            else
                a -= '0';
            if (b >= 'a')
                b -= 'a' - 'A';
            if (b >= 'A')
                b -= ('A' - 10);
            else
                b -= '0';
            returnable.push_back(16 * a + b);
            src += 3;
        } else if (*src == '+') {
            returnable.push_back(' ');
            src++;
        } else {
            returnable.push_back(*src++);
        }
    }
    return returnable;
}

