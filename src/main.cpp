#include <dpp/dpp.h>
#include <stdio.h>
#include <cstdint>
#include <string>

const std::string    BOT_TOKEN    = ""; 
static int32_t message_count = 0;

int main() {
    dpp::cluster bot(BOT_TOKEN);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            std::cout << "Ponging\n";
            event.reply("Boar from CPP!");
        }
    });


    bot.on_slashcommand([message_count](const dpp::slashcommand_t &event) {
		if (event.command.get_command_name() == "messages") {
			std::string message = "Contagem de mensagens: ";
			message += std::to_string(message_count);
			event.reply(message);
		}
	});

	/* Message handler */
	bot.on_message_create(
		[&](const dpp::message_create_t &event) { message_count++; });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(
                    dpp::slashcommand("ping", "Ping pong!", bot.me.id)
            );
            bot.global_command_create(
                    dpp::slashcommand("messages", "Messages registered since i started", bot.me.id)
            );
        }
    });

    bot.on_guild_member_add( [](const dpp::guild_member_add_t& event)
    {
        std::cout << "Someone joined!!\n";
    });

    bot.start(dpp::st_wait);
}