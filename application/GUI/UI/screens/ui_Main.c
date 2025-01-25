/*
 * ui_Main.c
 *
 *  Created on: Jan 25, 2025
 *      Author: hzaib
 */


#include "ui.h"
#include "Defines.h"
#include "utc_clock.h"
#include "stdio.h"
#include "string.h"
#include "cui.h"

//int gmt = 5;

#define LV_COLOR_RED     0xFF0000
#define LV_COLOR_GREEN   0x008000
#define LV_COLOR_BLUE    0x0000FF
#define LV_COLOR_ORANGE  0xFFA500
#define LV_COLOR_PURPLE  0xA020F0
#define LV_COLOR_WHITE   0xFFFFFF

 uint32_t tableColors[] = {
  LV_COLOR_RED,
  LV_COLOR_GREEN,
  LV_COLOR_BLUE,
  LV_COLOR_ORANGE,
  LV_COLOR_PURPLE
};


const int maxTables = sizeof(tableColors) / sizeof(tableColors[0]);


#define MAX_MESSAGES 30 // or 20 as desired

typedef struct {
    uint8_t tableNumber;
    char timeText[10];   // e.g., "0.34 Sec", "1.43 Min"
} message_t;

static message_t messages[MAX_MESSAGES];
static int messageCount = 0; // Current number of messages in the ring buffer

static int current_scroll_y = 0; // track our manual scroll offset

const char *waiterName = "John Doe";
int connectedTables = 3;

// LVGL objects
lv_obj_t* ui_Main;
lv_obj_t* time_label;
lv_obj_t* date_label;
lv_obj_t* waiter_label;
lv_obj_t* waiter_icon;
lv_obj_t* waiter_name_label;
lv_obj_t* tables_connected_label;
lv_obj_t* message_container;

// Styles
static lv_style_t style_time_date;
static lv_style_t style_waiter_name;
static lv_style_t style_tables_connected;


static void add_message(uint8_t tableNum, const char* timeStr)
{
    // If buffer not full, increment messageCount
    if (messageCount < MAX_MESSAGES) {
        messageCount++;
    }

    // Shift messages down (from bottom to top)
    for (int i = messageCount - 1; i > 0; i--) {
        messages[i] = messages[i - 1];
    }

    // Insert new message at the top
    messages[0].tableNumber = tableNum;
    strncpy(messages[0].timeText, timeStr, sizeof(messages[0].timeText) - 1);
    messages[0].timeText[sizeof(messages[0].timeText) - 1] = '\0';
}

static void refresh_message_list(void)
{
    // Clear the container of existing children
    lv_obj_clean(message_container);

    // Re-create each message entry in order
    for (int i = 0; i < messageCount; i++) {
        // Create a container or button for each message
        lv_obj_t* msg_item = lv_obj_create(message_container);
        lv_obj_set_size(msg_item, LV_PCT(100), LV_SIZE_CONTENT); // Fill width, auto height
        lv_obj_set_style_bg_opa(msg_item, LV_OPA_COVER, 0);

        // Optionally color-code the background based on time or table
        // For example, table 1 might be green, table 21 might be yellow, etc.
        // Or parse the time string to decide color if time is >2 min, etc.
        // Example pseudo-code:
        // if (strstr(messages[i].timeText, "Sec")) { // green
        //     lv_obj_set_style_bg_color(msg_item, lv_color_make(0x80, 0xFF, 0x80), 0);
        // }

        // Create a horizontal container inside for icon + table + time
        lv_obj_set_flex_flow(msg_item, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(msg_item, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        // Table Icon
        lv_obj_t* icon = lv_label_create(msg_item);
        lv_label_set_text(icon, LV_SYMBOL_HOME); // or a custom icon
        lv_obj_set_style_text_font(icon, &lv_font_montserrat_16, 0);
        lv_obj_set_style_text_color(icon, lv_color_black(), 0);

        // Table Number
        char tableStr[16];
        snprintf(tableStr, sizeof(tableStr), " Table %d ", messages[i].tableNumber);
        lv_obj_t* table_label = lv_label_create(msg_item);
        lv_label_set_text(table_label, tableStr);
        lv_obj_set_style_text_font(table_label, &lv_font_montserrat_16, 0);
        lv_obj_set_style_text_color(table_label, lv_color_black(), 0);

        // Time Text
        lv_obj_t* time_label = lv_label_create(msg_item);
        lv_label_set_text(time_label, messages[i].timeText);
        lv_obj_set_style_text_font(time_label, &lv_font_montserrat_16, 0);
        lv_obj_set_style_text_color(time_label, lv_color_black(), 0);

        // You can do more advanced color coding, icons, etc. inside each item
    }

    // After creating all items, LVGL will handle scrolling for you
    // The newest message is at index 0, so it appears at the top
}


static void ui_Main_screen_updateTimeDate()
{
    static char timeStr[15];
    static char dateStr[15];
    uint32_t time =UTC_getClock();
      UTCTimeStruct tm;
      EPOCH_convertTime(&tm,time,gmt);



      sprintf(timeStr,"%02d:%02d",tm.hour, tm.minutes);
      sprintf(dateStr,"%02d/%02d/%02d", tm.day, tm.month, tm.year);




      // Update the labels
      lv_label_set_text(time_label,(const char *) timeStr);
      lv_label_set_text(date_label,(const char *) dateStr);
}

 void update_callback(lv_timer_t *timer) {

    // Update the time and date
     ui_Main_screen_updateTimeDate();
     refresh_message_list();
    // ui_Main_scroll_list();
}

 void ui_Main_descroll_list()
 {
     // Increase the scroll offset by 30
        current_scroll_y -= 20;

        // Clamp so we don’t scroll past the container’s content
        int content_h = lv_obj_get_content_height(message_container);  // total content height
        int container_h = lv_obj_get_height(message_container);        // visible container height

 //       // If content is smaller than the container, no need to scroll
 //       if (content_h > container_h) {
 //           int max_offset = content_h - container_h;
 //           if (current_scroll_y > max_offset) {
 //               current_scroll_y = max_offset;
 //           }
            // Now scroll the container to that offset
            lv_obj_scroll_to_y(message_container, current_scroll_y, LV_ANIM_OFF);
        //}
 }

 void ui_Main_scroll_list()
 {
     // Increase the scroll offset by 30
       current_scroll_y += 20;

       // Clamp so we don’t scroll past the container’s content
       int content_h = lv_obj_get_content_height(message_container);  // total content height
       int container_h = lv_obj_get_height(message_container);        // visible container height

//       // If content is smaller than the container, no need to scroll
//       if (content_h > container_h) {
//           int max_offset = content_h - container_h;
//           if (current_scroll_y > max_offset) {
//               current_scroll_y = max_offset;
//           }
           // Now scroll the container to that offset
           lv_obj_scroll_to_y(message_container, current_scroll_y, LV_ANIM_OFF);
       //}
 }

 void ui_Main_new_message(uint8_t tableNum, const char* timeStr)
 {
     add_message(tableNum,timeStr);
 }


void ui_Main_screen_init()
{



    ui_Main = lv_obj_create(NULL);
    // Set the background color of the active screen to black
     lv_obj_set_style_bg_color(ui_Main, lv_color_black(), LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_bg_opa(ui_Main, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);

     // Style for Time and Date
     lv_style_init(&style_time_date);
     lv_style_set_text_color(&style_time_date, lv_color_hex(LV_COLOR_WHITE));
     lv_style_set_text_font(&style_time_date, &lv_font_montserrat_16);

     // Style for Waiter Name
     lv_style_init(&style_waiter_name);
     lv_style_set_text_color(&style_waiter_name, lv_color_hex(LV_COLOR_WHITE)); // White text
     lv_style_set_text_font(&style_waiter_name,&lv_font_montserrat_18); // Font size 18

     // Style for Tables Connected
     lv_style_init(&style_tables_connected);
     lv_style_set_text_color(&style_tables_connected,lv_color_hex(LV_COLOR_WHITE)); // White text
     lv_style_set_text_font(&style_tables_connected, &lv_font_montserrat_16); // Font size 16


     time_label = lv_label_create(ui_Main);
     lv_obj_add_style(time_label, &style_time_date, LV_STATE_DEFAULT);
     lv_label_set_text(time_label, "00:00");
     lv_obj_align(time_label, LV_ALIGN_TOP_LEFT, 10, 10);


     // Date Label - Top Right
     date_label = lv_label_create(ui_Main);
     lv_obj_add_style(date_label, &style_time_date, LV_STATE_DEFAULT);
     lv_label_set_text(date_label, "01/01/2025");
     lv_obj_align(date_label, LV_ALIGN_TOP_RIGHT, -10, 10);


       // Add a picture icon (Using an Emoji as a Placeholder)
     waiter_icon = lv_label_create(ui_Main);
     lv_label_set_text(waiter_icon, "\xEF\x80\x87"); // Placeholder icon
     lv_obj_add_style(waiter_icon, &style_waiter_name, LV_STATE_DEFAULT); // Apply waiter name style for consistency
     lv_obj_set_style_text_font(waiter_icon, &lv_font_montserrat_20, LV_STATE_DEFAULT); // Larger font for icon
     lv_obj_align(waiter_icon, LV_ALIGN_TOP_LEFT, 10, 40); // Position 60px above bottom left


       // Add Waiter Name Label
     waiter_name_label = lv_label_create(ui_Main);
     lv_label_set_text(waiter_name_label, waiterName);
     lv_obj_add_style(waiter_name_label, &style_waiter_name, LV_STATE_DEFAULT);
     lv_obj_align(waiter_name_label,LV_ALIGN_TOP_LEFT, 25, 40 ); // Align to the right of the icon



       // Add Spacer between Name and Tables Connected
     lv_obj_t* spacer = lv_obj_create(ui_Main);
     lv_obj_set_size(spacer, 20, 1); // 20px spacer
     lv_obj_align(spacer,LV_ALIGN_TOP_LEFT, 120, 50);

       // Add Tables Connected Label
     tables_connected_label = lv_label_create(ui_Main);
     char tablesText[20];
     snprintf(tablesText, sizeof(tablesText), "Tables: %d", connectedTables);
     lv_label_set_text(tables_connected_label, tablesText);
     lv_obj_add_style(tables_connected_label, &style_tables_connected, LV_STATE_DEFAULT);
     lv_obj_align(tables_connected_label,LV_ALIGN_TOP_LEFT, 150, 40);

     // Create a container that will hold messages
      message_container = lv_obj_create(ui_Main);
      lv_obj_set_size(message_container, 220, 200); // Adjust as needed
      lv_obj_align(message_container, LV_ALIGN_BOTTOM_MID, 0, -10); // Position near bottom

      // Enable scrolling in vertical direction
         lv_obj_set_scroll_dir(message_container, LV_DIR_VER);
         lv_obj_set_scrollbar_mode(message_container, LV_SCROLLBAR_MODE_AUTO);

         // Use a column layout for child items
         lv_obj_set_flex_flow(message_container, LV_FLEX_FLOW_COLUMN);
         // Align items from top to bottom
         lv_obj_set_flex_align(message_container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

         // Optional: Black or White background depending on your theme
         lv_obj_set_style_bg_color(message_container, lv_color_black(), 0);
         lv_obj_set_style_bg_opa(message_container, LV_OPA_COVER, 0);


     ui_Main_screen_updateTimeDate();
     // Add some sample messages
      add_message(1, "0.34 Sec");
      add_message(21, "1.43 Min");
      add_message(18, "2.12 Min");
      add_message(18, "5.12 Min");
      add_message(21, "6.12 Min");
      add_message(21, "1.43 Min");
         add_message(1, "2.12 Min");
         add_message(18, "5.12 Min");
         add_message(21, "6.12 Min");
         add_message(21, "1.43 Min");
            add_message(18, "2.12 Min");
            add_message(18, "5.12 Min");
            add_message(21, "6.12 Min");
            add_message(21, "1.43 Min");
               add_message(18, "2.12 Min");
               add_message(18, "5.12 Min");
               add_message(21, "6.12 Min");
      refresh_message_list();

     // Set up a timer to update the time and date every second
    // lv_obj_t *user_data[2] = {time_label, date_label}; // Store labels in user data
     lv_timer_create(update_callback, 1000, NULL); // 60 second



}
