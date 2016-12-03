
module.exports = [{
  "type": "text",
  "defaultValue": "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<svg version=\"1.1\" baseProfile=\"tiny\" id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n\t x=\"0px\" y=\"0px\" viewBox=\"0 0 960 560\" xml:space=\"preserve\">\n<path fill=\"#FFFFFF\" stroke=\"#000000\" stroke-width=\"21.6401\" stroke-linecap=\"round\" stroke-linejoin=\"round\" stroke-miterlimit=\"10\" d=\"\n\tM625.7,194.1l-26-22.8c0-26.4,24.4-47.8,54.5-47.8c30.1,0,54.5,21.4,54.5,47.8L720,282.1l-126.3-79.2L625.7,194.1z\"/>\n<path fill=\"#FFFFFF\" stroke=\"#000000\" stroke-width=\"21.6401\" stroke-linecap=\"round\" stroke-linejoin=\"round\" stroke-miterlimit=\"10\" d=\"\n\tM363.1,194.1l26-22.8c0-26.4-24.4-47.8-54.5-47.8S280,144.9,280,171.3l-11.3,110.7L395,202.9L363.1,194.1z\"/>\n<g>\n\t<path fill=\"#FFFFFF\" d=\"M494.4,122.4c-46.3,0-107,20.4-134.9,45.3c-27.9,24.9-50.7,87.5-50.7,139s13.5,105.8,30,120.5\n\t\ts77.2,26.8,134.8,26.8h41.6c57.6,0,118.3-12.1,134.8-26.8c16.5-14.8,30-69,30-120.5s-22.8-114.1-50.7-139S540.7,122.4,494.4,122.4z\n\t\t\"/>\n\t\n\t\t<path fill=\"none\" stroke=\"#000000\" stroke-width=\"21.6401\" stroke-linecap=\"round\" stroke-linejoin=\"round\" stroke-miterlimit=\"10\" d=\"\n\t\tM494.4,122.4c-46.3,0-107,20.4-134.9,45.3c-27.9,24.9-50.7,87.5-50.7,139s13.5,105.8,30,120.5s77.2,26.8,134.8,26.8h41.6\n\t\tc57.6,0,118.3-12.1,134.8-26.8c16.5-14.8,30-69,30-120.5s-22.8-114.1-50.7-139S540.7,122.4,494.4,122.4z\"/>\n</g>\n<path fill=\"#FFFFFF\" stroke=\"#000000\" stroke-width=\"18.4783\" stroke-linecap=\"round\" stroke-linejoin=\"round\" stroke-miterlimit=\"10\" d=\"\n\tM610.3,349.8c0,81.4-51.9,87.8-115.9,87.8s-115.9-6.5-115.9-87.8c0-48.5,51.9-87.8,115.9-87.8S610.3,301.3,610.3,349.8z\"/>\n<polygon stroke=\"#000000\" stroke-width=\"6.1594\" stroke-linecap=\"round\" stroke-linejoin=\"round\" stroke-miterlimit=\"10\" points=\"\n\t467.1,259.6 521.7,259.6 494.4,290.1 \"/>\n<polyline fill=\"none\" stroke=\"#000000\" stroke-width=\"15.3986\" stroke-linecap=\"round\" stroke-linejoin=\"round\" stroke-miterlimit=\"10\" points=\"\n\t560.6,349.2 494.4,316.1 428.2,349.2 \"/>\n<line fill=\"none\" stroke=\"#000000\" stroke-width=\"15.3986\" stroke-linecap=\"round\" stroke-linejoin=\"round\" stroke-miterlimit=\"10\" x1=\"494.4\" y1=\"316.1\" x2=\"494.4\" y2=\"269.7\"/>\n<path fill=\"#FFFFFF\" stroke=\"#000000\" stroke-width=\"15.3986\" stroke-linecap=\"round\" stroke-linejoin=\"round\" stroke-miterlimit=\"10\" d=\"\n\tM343.5,180.1c0-23.3,26-42.2,58.1-42.2s56.6,8.6,68.9,34.2\"/>\n<path fill=\"#E6E7E8\" stroke=\"#231F20\" stroke-width=\"6.1594\" stroke-linecap=\"round\" stroke-miterlimit=\"10\" d=\"M389.3,222.2\"/>\n<g>\n\t<circle fill=\"#FFFFFF\" stroke=\"#000000\" stroke-width=\"15.3986\" stroke-miterlimit=\"10\" cx=\"398\" cy=\"228.3\" r=\"56.3\"/>\n\t<circle cx=\"388.8\" cy=\"228.3\" r=\"25.4\"/>\n\t<circle fill=\"#FFFFFF\" cx=\"374.9\" cy=\"214.4\" r=\"11.5\"/>\n</g>\n<path fill=\"#FFFFFF\" stroke=\"#000000\" stroke-width=\"15.3986\" stroke-linecap=\"round\" stroke-linejoin=\"round\" stroke-miterlimit=\"10\" d=\"\n\tM645.3,180.1c0-23.3-26-42.2-58.1-42.2s-56.6,8.6-68.9,34.2\"/>\n<g>\n\t<circle fill=\"#FFFFFF\" stroke=\"#000000\" stroke-width=\"15.3986\" stroke-miterlimit=\"10\" cx=\"590.8\" cy=\"228.3\" r=\"56.3\"/>\n\t<circle cx=\"599.9\" cy=\"228.3\" r=\"25.4\"/>\n\t<circle fill=\"#FFFFFF\" cx=\"613.9\" cy=\"214.4\" r=\"11.5\"/>\n</g>\n</svg>\n",
},
{
  "type": "section",
  "capabilities": ["BW"],
  "items": [
      {
        "type": "heading",
        "defaultValue": "Theme"
      },
      {
      "type": "radiogroup",
      "messageKey": "theme_bw",
      "defaultValue": "1",
      "label": "Background/Time Theme",
      "options": [
        {
          "label": "Light",
          "value": 1
        },
        {
          "label": "Grey",
          "value": 0
        },
        {
          "label": "Dark",
          "value": 2
        }
      ]
    }

  ]
},
{
  "type": "section",
  "capabilities": ["COLOR"],
  "items": [
      {
        "type": "heading",
        "defaultValue": "Theme"
      },
      {
        "type": "color",
        "messageKey": "theme_main_bg",
        "defaultValue": "aaaaaa",
        "label": "Background Color",
        "sunlight": false
      },
      {
        "type": "color",
        "messageKey": "theme_main_time",
        "defaultValue": "000000",
        "label": "Time Color",
        "sunlight": false
      }

  ]
},
{
  "type": "submit",
  "defaultValue": "Save"
}
]
