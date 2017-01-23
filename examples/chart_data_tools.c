/*
 * A demo of an various Excel chart data tools that are available via a
 * libxlsxwriter chart.
 *
 * These include Drop Lines and High-Low Lines.
 *
 * Copyright 2014-2017, John McNamara, jmcnamara@cpan.org
 *
 */

#include "xlsxwriter.h"

/*
 * Write some data to the worksheet.
 */
void write_worksheet_data(lxw_worksheet *worksheet, lxw_format *bold) {

    int row, col;
    uint8_t data[6][3] = {
        /* Three columns of data. */
        {2, 10, 30},
        {3, 40, 60},
        {4, 50, 70},
        {5, 20, 50},
        {6, 10, 40},
        {7, 50, 30}
    };

    worksheet_write_string(worksheet, CELL("A1"), "Number",  bold);
    worksheet_write_string(worksheet, CELL("B1"), "Batch 1", bold);
    worksheet_write_string(worksheet, CELL("C1"), "Batch 2", bold);

    for (row = 0; row < 6; row++)
        for (col = 0; col < 3; col++)
            worksheet_write_number(worksheet, row + 1, col, data[row][col] , NULL);
}

/*
 * Create a worksheet with examples charts.
 */
int main() {

    lxw_workbook     *workbook  = new_workbook("chart_data_tools.xlsx");
    lxw_worksheet    *worksheet = workbook_add_worksheet(workbook, NULL);

    /* Add a bold format to use to highlight the header cells. */
    lxw_format *bold = workbook_add_format(workbook);
    format_set_bold(bold);

    /* Write some data for the chart. */
    write_worksheet_data(worksheet, bold);


    /*
     * Chart 1. Example with High Low Lines.
     */
    lxw_chart *chart = workbook_add_chart(workbook, LXW_CHART_LINE);

    /* Add a chart title. */
    chart_title_set_name(chart, "Chart with High-Low Lines");

    /* Add the first series to the chart. */
    chart_add_series(chart, "=Sheet1!$A$2:$A$7", "=Sheet1!$B$2:$B$7");
    chart_add_series(chart, "=Sheet1!$A$2:$A$7", "=Sheet1!$C$2:$C$7");

    /* Add high-low lines to the chart. */
    chart_set_high_low_lines(chart, NULL);

    /* Insert the chart into the worksheet. */
    worksheet_insert_chart(worksheet, CELL("E2"), chart);


    /*
     * Chart 2. Example with Drop Lines.
     */
    chart = workbook_add_chart(workbook, LXW_CHART_LINE);

    /* Add a chart title. */
    chart_title_set_name(chart, "Chart with Drop Lines");

    /* Add the first series to the chart. */
    chart_add_series(chart, "=Sheet1!$A$2:$A$7", "=Sheet1!$B$2:$B$7");
    chart_add_series(chart, "=Sheet1!$A$2:$A$7", "=Sheet1!$C$2:$C$7");

    /* Add drop lines to the chart. */
    chart_set_drop_lines(chart, NULL);

    /* Insert the chart into the worksheet. */
    worksheet_insert_chart(worksheet, CELL("E18"), chart);


    /*
     * Chart 3. Example with Up-Down bars.
     */
    chart = workbook_add_chart(workbook, LXW_CHART_LINE);

    /* Add a chart title. */
    chart_title_set_name(chart, "Chart with Up-Down bars");

    /* Add the first series to the chart. */
    chart_add_series(chart, "=Sheet1!$A$2:$A$7", "=Sheet1!$B$2:$B$7");
    chart_add_series(chart, "=Sheet1!$A$2:$A$7", "=Sheet1!$C$2:$C$7");

    /* Add Up-Down bars to the chart. */
    chart_set_up_down_bars(chart);

    /* Insert the chart into the worksheet. */
    worksheet_insert_chart(worksheet, CELL("E34"), chart);


    /*
     * Chart 4. Example with Up-Down bars with formatting.
     */
    chart = workbook_add_chart(workbook, LXW_CHART_LINE);

    /* Add a chart title. */
    chart_title_set_name(chart, "Chart with Up-Down bars");

    /* Add the first series to the chart. */
    chart_add_series(chart, "=Sheet1!$A$2:$A$7", "=Sheet1!$B$2:$B$7");
    chart_add_series(chart, "=Sheet1!$A$2:$A$7", "=Sheet1!$C$2:$C$7");

    /* Add Up-Down bars to the chart, with formatting. */
    lxw_chart_line line      = {.color = LXW_COLOR_BLACK};
    lxw_chart_fill up_fill   = {.color = 0x00B050};
    lxw_chart_fill down_fill = {.color = LXW_COLOR_RED};

    chart_set_up_down_bars_format(chart, &line, &up_fill, &line, &down_fill);
    
    /* Insert the chart into the worksheet. */
    worksheet_insert_chart(worksheet, CELL("E50"), chart);


    return workbook_close(workbook);
}